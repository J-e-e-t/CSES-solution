/*
Distinct Values Queries

You are given an array of n integers and q queries of the form: how many distinct values are there in a range [a,b]?

Input

The first input line has two integers n and q: the array size and number of queries.

The next line has n integers x1,x2,…,xn: the array values.

Finally, there are q lines describing the queries. Each line has two integers a and b.

Output

For each query, print the number of distinct values in the range.

Constraints

    1≤n,q≤2⋅105


1≤xi≤109

1≤a≤b≤n


Example

Input:
5 3
3 2 3 1 2
1 3
2 4
1 5

Output:
2
3
3
*/

/*
This is a direct application of the MO's Algorithm. You may read more about MO's algorithm on https://blog.anudeep2011.com/mos-algorithm/

The brute force can be done by simply iterating from index a to b and maintaining number of distinct elements seen till now and a frequency array to indicate which elements and how many occurrences of those elements is present.

Frequency[i] = count of occurences of i in the current range.

Next we try to build the required ADD and REMOVE functions which help MO's algorithm to function properly.
To ADD a new element in the current range simply check if this element is already present(frequency > 0) and if it is present just increase its frequency else if its frequency was 0 then make it 1 and also increase the number of unique elements in the range.
To REMOVE an element from the current range, decrement its frequency by 1, if its frequency reaches 0 then decrease the number of distinct elements in the current range.

After this sort the queries as described by MO's algorithm and you are done.

Twist : We cannot use frequency array as value of individual element can go upto 10^9. So what I'll simply use an unordered_map?

No, unordered_map solution will time out due to high constant factor involved.

How to continue using the frequency array?

Coordinate compression, simply map larger values to smaller values in the range [1,N] and you are done as N can be atmost 2*10^5.

We can do this because we don't really care about the actual values but only about the number of unique values in a range.

Time complexity : O((N+Q)root(N))

AC code : https://ideone.com/RkC547

*/

/*
    author: kartik8800
*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(ll i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
const int rootN = 555;

int freq[200000];
int distinct;
int ar[200000];

struct query
{
    int L;
    int R;
    int q_no;
    int block_no;
    bool operator < (query& q2)
    {
        if(block_no < q2.block_no)
            return 1;
        else if(block_no > q2.block_no)
            return 0;
        else return R < q2.R;
    }
};

void Add(int& elem)
{
    if(!freq[elem])distinct++;
    freq[elem]++;
}
void Remove(int& elem)
{
    freq[elem]--;
    if(!freq[elem])
        distinct--;
}

void adjust(int& curr_l, int& curr_r, query& q)
{
    while(curr_l > q.L)
    {
        curr_l--;
        Add(ar[curr_l]);
    }
    while(curr_r < q.R)
    {
        curr_r++;
        Add(ar[curr_r]);
    }
	while(curr_l < q.L)
    {
        Remove(ar[curr_l]);
        curr_l++;
    }
    while(curr_r > q.R)
    {
        Remove(ar[curr_r]);
        curr_r--;
    }

}

void solve(vector<query>& queries)
{
    vector<int> answer(queries.size());
    sort(queries.begin(), queries.end());
    memset(freq, 0, sizeof freq);
    distinct = 1;

    int curr_l = queries[0].L;
    int curr_r = queries[0].L;

    freq[ar[curr_l]]++;

    for(query& qr : queries)
    {
        adjust(curr_l, curr_r, qr);
        answer[qr.q_no] = distinct;
    }

    for(int x : answer)
            cout<<x<<'\n';
}

int main() {
   fast_io;
   int n,q;
   cin >> n >> q;

   map<int,int> coordinateCompress;
   int compressed_Num = 1;

   for(int i = 0; i < n; i++)
   {
       cin >> ar[i];
       if(coordinateCompress.find(ar[i]) != coordinateCompress.end()){
        ar[i] = coordinateCompress[ar[i]];
       }
       else{
        coordinateCompress[ar[i]] = compressed_Num;
        ar[i] = compressed_Num++;
       }
   }

   vector<query> queries(q);
   for(int i = 0; i < q; i++)
   {
       int u,v;
       cin >> u >>v;
       queries[i].L = u-1;
       queries[i].R = v-1;
       queries[i].q_no = i;
       queries[i].block_no = u/rootN;
   }
   solve(queries);
   return 0;
}


//Usaco

// Hint

// Sort the queries in a specific order before answering them.

/*
Solution
Time Complexity: $\mathcal{O}(N\log{N})$We answer the queries from right to left, sorted by their left indices. By using a BIT, we can keep track of indices that contain distinct values. For every value $arr[i]$, we set the latest (i.e. the left-most) index in $bit[i]$ to $1$. If this value appeared before, we set the last used index back to $0$. Then, we can answer all queries with $a = i$ by summing up the values between $[i, b]$. This ensures later indices after $i$ are included in the BIT to accurately answer queries.
*/


// #include <bits/stdc++.h>
// using namespace std;

// //BeginCodeSnip{BIT}
// struct BIT {
// 	int size;
// 	vector<int> bit;
// 	BIT(int n) : size(n), bit(n + 1) {}
// 	void update(int x, int v) {
// 		x++;
// 		for (; x <= size; x += x & (-x)) {
// 			bit[x] += v;
// 		}
// 	}
// 	/** @return sum of the values in [0,b] */
// 	int query(int b) {
// 		b++;
// 		int result = 0;
// 		for (; b > 0; b -= b & (-b)) {
// 			result += bit[b];
// 		}
// 		return result;
// 	}
// };
// //EndCodeSnip

// int main() {
// 	int n, q;
// 	cin >> n >> q;

// 	vector<int> arr(n);
// 	vector<vector<pair<int, int>>> queries(n);
// 	for (int i = 0; i < n; i++) {
// 		cin >> arr[i];
// 	}
// 	for (int i = 0; i < q; i++) {
// 		int a, b;
// 		cin >> a >> b;
// 		a--, b--;
// 		queries[a].push_back({b, i});
// 	}

// 	BIT bit(n);
// 	// last_index[val] is the left-most index where arr[last_index[val]] = val.
// 	map<int, int> last_index;
// 	vector<int> solution(q, -1);
// 	// Update the indices and answer queries from right to left.
// 	for (int i = n - 1; i >= 0; i--) {
// 		int val = arr[i];
// 		/*
// 		 * If val already appeared earlier, then the saved value is no
// 		 * longer the left-most index, so erase it from our BIT.
// 		 */
// 		if (last_index.count(val) > 0) bit.update(last_index[val], -1);
// 		// i becomes the left-most index.
// 		last_index[val] = i;
// 		bit.update(i, 1);

// 		// Answer all queires with a == i.
// 		for (auto &qr : queries[i]) {
// 			/*
// 			 * The solution for this query is bit[i,b].
// 			 * This equals bit[0,b] since bit[0,i-1] = 0.
// 			 */
// 			solution[qr.second] = bit.query(qr.first);
// 		}
// 	}

// 	for (auto &a : solution) {
// 		cout << a << "\n";
// 	}
// }

