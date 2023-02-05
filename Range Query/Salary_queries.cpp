/*Salary Queries

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

A company has n
employees with certain salaries. Your task is to keep track of the salaries and process queries.

Input

The first input line contains two integers n and q: the number of employees and queries. The employees are numbered 1,2,…,n.

The next line has n integers p1,p2,…,pn: each employee's salary.

After this, there are q lines describing the queries. Each line has one of the following forms:

    ! k

x: change the salary of employee k to x

? a
b: count the number of employees whose salary is between a…b


Output

Print the answer to each ? query.

Constraints

    1≤n,q≤2⋅105


1≤pi≤109

1≤k≤n

1≤x≤109

1≤a≤b≤109


Example

Input:
5 3
3 7 2 2 5
? 2 3
! 3 6
? 2 3

Output:
3
2
*/

/*
Okay so, this seems a bit hard. Maybe if the max possible salary of the employees was limited to some smaller amount(instead of a billion) we might be able to solve it.

So try solving the problem under the constraint that p,a,b <= 10^7.
Now the problem is much easier if I maintain the number of people with a given salary, let us define
freq[i] : number of employees with the salary i
We may now build a range sum query segment tree on this array and to answer a query we simply calculate the sum of the range [a,b].

For updating the salary of some employee from x to y, we do the point updates freq[x] -= 1 and freq[x] += 1 because now 1 less employee has salary x and 1 more employee has the salary y.

But the problem is not solved, since we needed to do this for max possible salary = 1billion, but now we know how to do it for 10^7.

10^9 = 10^7 * 10^2


So lets group the salaries into 10^7 buckets and each bucket represent a range of 100 different contiguous salary values. The 0th bucket represents salaries from 1 to 100 and ith bucket represents the salaries from (i)*100 + 1 to (i+1)*100.

These buckets will store aggregated number of employees that have salaries in the given range represented by the bucket.

Now for query [a,b] : all the buckets that are entirely in the range [a,b] their aggregate values should be taken and summed up and for the 2 partial buckets(or 1) not entirely included in the range [a,b] we shall do a brute force.

So build a segment tree over the buckets and calculate the sum over all completely included buckets in the range [a,b]. For remaining partially included buckets do a brute force(actually iterate over approx 100 possible values and choose to include those which are required by a particular query, refer code).

A code will make this explanation much more clear.

proportional to 10^7 operations to build the tree, per range sum query and per point update operations proportional to log(10^7). Accessing the map is proportional to logN operations, for left extreme and right extreme buckets we will need to do proportional to (logN + 100) operations.
Somewhat proportional to (10^7 + Qlog(10^7) + 200*Q + Q*logN) operations.

other way to do it is using a dynamic segment tree in which you only build a node of the tree when it is needed.*/

#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define ll long long
using namespace std;
#define left(i) (2*i + 1)
#define right(i) (2*i + 2)
#define parent(i) ((i-1)/2)
#include <vector>

template<class T>
class SegmentTree
{
    public:
        SegmentTree(std::vector<T> data, T value, T (*combine)(T obj1, T obj2));
        SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));
        T query(int l, int r);
        void update(int idx, T val);
        //TODO lazy propagation
    private:
        T *tree;
        void buildTree(std::vector<T> data);
        int segTreeSize;
        T valueForExtraNodes;
        T (*combine)(T obj1, T obj2);
        int calculateSize(int n);
        T queryHelper(int l,int r, int st, int ed, int node);
};

template<class T> SegmentTree<T>::SegmentTree(std::vector<T> data,
                                                T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   segTreeSize = calculateSize(data.size());
   buildTree(data);
}

template<class T> SegmentTree<T>::SegmentTree(T ar[], int n,
                                            T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   segTreeSize = calculateSize(n);

   std::vector<T> data;
   for(int i = 0; i < n; i++)
         data.push_back(ar[i]);

   buildTree(data);
}


template<class T> int SegmentTree<T>::calculateSize(int n)
{
    int pow2 = 1;
    while( pow2 < n)
    {
        pow2 = pow2 << 1;
    }
    return 2*pow2 - 1;
}

template<class T> T SegmentTree<T>::query(int l, int r)
{
    int st = 0, ed = segTreeSize/2;
    return queryHelper(l, r, st, ed, 0);
}

template<class T> T SegmentTree<T>::queryHelper(int l,int r, int st, int ed, int node)
{
    if( (r < st) || (l > ed) || (l > r) )
        return valueForExtraNodes;
    if(st >= l && ed <= r)
        return tree[node];
    T leftVal = queryHelper(l, r, st, (st + ed)/2, left(node));
    T rightVal = queryHelper(l, r, (st+ed)/2 + 1, ed, right(node));
    return combine(leftVal, rightVal);
}

template<class T> void SegmentTree<T>::buildTree(std::vector<T> data)
{
   int n = data.size();
   tree = new T[segTreeSize];
   int extraNodes = (segTreeSize/2 + 1) - n;
   for(int i = segTreeSize - 1; i >= 0; i--)
   {
       if(extraNodes>0)
           {
               tree[i] = valueForExtraNodes;
               extraNodes--;
           }
       else if(n>0)
           {
               tree[i] = data[n-1];
               n--;
           }
       else
           tree[i] = combine(tree[left(i)], tree[right(i)]);
   }
}

template<class T> void SegmentTree<T>::update(int idx, T val)
{
    int segTreeIdx = (segTreeSize/2) + idx;
    tree[segTreeIdx] = val;
    while(parent(segTreeIdx) >= 0)
    {
        segTreeIdx = parent(segTreeIdx);
        if(right(segTreeIdx) < segTreeSize)
          tree[segTreeIdx] = combine(tree[left(segTreeIdx)], tree[right(segTreeIdx)]);
        if(segTreeIdx == 0)
            break;
    }
}

// returns number of employees with salaries between lo and hi
int calc(int lo, int hi, map<int,int>& sal2freq)
{
    int res = 0;
    auto it = sal2freq.lower_bound(lo);
    while(it != sal2freq.end() && it->first <= hi){
        res += it->second;
        it++;
    }
    return res;
}
//returns the bucket number to which x belongs
int bucket_no(int x)
{
    // 1-100 in block 0 but 100/100 = 1
    if(x % 100 == 0)
        x--;
    return (x / 100);
}

int sum(int x,int y) { return x+y; }
int main()
{
    fast_io;
    int n,q;
    cin >> n >> q;

    vector < int > employee(n);
    vector< int > buckets(10000000, 0);

    // salary = key, number of employees with this salary = value
    map < int, int> salary2freq;

    for(int  i = 0 ; i < n; i++)
    {
        int salary;
        cin >> salary;

        employee[i] = salary;
        salary2freq[salary]++;

        buckets[bucket_no(salary)]++;
    }
    SegmentTree < int > rangeSumQueries(buckets, 0, sum);

    while(q--)
    {
        char ch;
        cin >> ch;
        if(ch == '!')
        {
            int k,x;
            cin >> k >> x;
            int prev_salary = employee[k-1];
            employee[k-1] = x;

            int prev_bucket = bucket_no(prev_salary);
            int new_bucket = bucket_no(x);

            buckets[prev_bucket]--;
            buckets[new_bucket]++;
            salary2freq[prev_salary]--;
            salary2freq[x]++;

            rangeSumQueries.update(prev_bucket, buckets[prev_bucket]);
            rangeSumQueries.update(new_bucket, buckets[new_bucket]);
        }
        else
        {
            int a,b;
            cin >> a >> b;

            int lbucket = bucket_no(a);
            int rbucket = bucket_no(b);

            int ans = calc(a, min((lbucket+1)*100, b), salary2freq);
            ans  = ans + ((lbucket!=rbucket) ? calc(max(a, rbucket*100 + 1), b, salary2freq) : 0);
            ans  = ans + rangeSumQueries.query(lbucket+1, rbucket-1);

            cout << ans << '\n';
        }
    }

    return 0;
}


//https://usaco.guide/problems/cses-1144-salary-queries/solution