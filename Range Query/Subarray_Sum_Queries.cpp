/*
Subarray Sum Queries

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

There is an array consisting of n
integers. Some values of the array will be updated, and after each update, your task is to report the maximum subarray sum in the array.

Input

The first input line contains integers n and m: the size of the array and the number of updates. The array is indexed 1,2,…,n.

The next line has n integers: x1,x2,…,xn: the initial contents of the array.

Then there are m lines describing the changes. Each line has two integers k and x: the value at position k becomes x.

Output

After each update, print the maximum subarray sum. Empty subarrays (with sum 0) are allowed.

Constraints

    1≤n,m≤2⋅105


−109≤xi≤109

1≤k≤n

−109≤x≤109


Example

Input:
5 3
1 2 -3 5 -1
2 6
3 1
2 -2

Output:
9
13
6
*/

//codeforces

/*
Let us try to keep track of the max sum subarray in a particular range [L,R]. If we were to build a segment tree in which each node of the tree stores max sum subarray of the range that the node is responsible for then the root keeps track of max sum subarray in the range [1,N].
However for segment trees to be efficient we need to generate the answer of interior nodes of the tree using the answers/information provided by the child nodes.

Now let's try to generate the answer for some interior node P of the segment tree assuming that we already have the answers for the children of the node P.

Node P is responsible for the range [l,r], its left child is responsible for the range [l,mid] and its right child is responsible for the range [mid+1,r].

Now we need to find the sum of max sum subarray in the range [l,r].
Assume you have all necessary information about the child nodes but if you have some information about a child node you also need to generate that piece of information for the parent node as well(since this node also has a parent which will use information given by P to generate it's answer).

How to relate the answer for parent to the answers about children?

Consider the following possibilities regarding max sum subarray in range [l,r]:
1. It might lie entirely in the range [l,mid] or entirely in range [mid+1,r].
2. It might be some subarray [p,q] such p <= mid and q > mid

Agreed, now what info to keep for every node?

We need to cover all the possibilities discussed above.
If subarray lies entirely in [l,mid] then my subarray for [l,r] is the same as that for [l,mid] and so is the sum, so it is required to know the sum of max sum subarray of range [l,mid] and on similar lines we also need to know sum of max sum subarray of range [mid+1,r].
Now try and think what property is useful to calculate the maximum sum subarray [p,q] such p <= mid and q > mid.
The subarray [p,q] is the union of the subarrays [p,mid] and [mid+1,q]. Among all possible [p,mid] subarrays we should choose p(l<=p<=mid) such that sum of elements in range [p,mid] is maximized and similarly among all possible values of q(mid+1<=q<=r) we should choose q such that sum of elements in range [mid+1,q] is maximized, maximizing these two individually is equivalent to maximizing [p,q].
Call [p,mid] as the suffix and [mid+1,q] as prefix. Our max sum subarray [p,q] such that p <= mid and q > mid is nothing but (suffix_of_left_child) UNION (prefix_of_right_child).

So to summarize, for every node which represents the range [l,r] we should store :
1. sum of max sum subarray in the range [l,r].
2. maximum possible sum of some prefix [l,x] (such value of x is chosen, such that l <= x <= r and sum of elements in range [l,x] is maximum possible.)
3. maximum possible sum of some suffix [x,r].

We now know how to calculate sum of max sum subarray for some node using the above mentioned information about children nodes but as discussed we should also calculate prefix and suffix info for the parent also.


How to calculate prefix and suffix for parent node?

The maximum sum prefix could be the same as prefix_of_left_child or it could be the entire left_child_range UNION prefix_of_right_child.

But now we need the sum of elements of left_child_range as well, which is the sum of all elements in [l,mid]. So this is another information we should store for every node.

Similarly the maximum sum suffix could be the same as suffix_of_right_child or it could be the entire right_child_range UNION suffix_of_left_child. 

Refer the combine function in the code for more clarity.
AC code : https://ideone.com/MhVmBs

Time complexity : logN per update.

*/


/*
    author: kartik8800
*/

/*
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

// SEGMENT TREE NODE WITH REQUIRED INFO
struct node
{
    ll maxSumSub;
    ll sumOfAllElements;
    ll prefix;
    ll suffix;
    node(){}
    // For a leaf node, all these values are simply equal to A[x] if
    // node represents range [x,x]
    node(ll val)
        {maxSumSub = sumOfAllElements = prefix = suffix = val;}
};

//Generate result for parent node using child nodes.
node combine(node x,node y)
{
    node *ptr = new node();
    // either left ans or right ans
    ptr->maxSumSub = max(x.maxSumSub, y.maxSumSub);
    // or of form suffix UNION prefix
    ptr->maxSumSub = max(ptr->maxSumSub, x.suffix + y.prefix);
    // as discussed
    ptr->prefix = max(x.prefix, x.sumOfAllElements + y.prefix);
    // as discussed
    ptr->suffix = max(y.suffix, y.sumOfAllElements + x.suffix);
    // sum of all elements of range [l,mid] and that of [mid+1,r]
    ptr->sumOfAllElements = x.sumOfAllElements + y.sumOfAllElements;
    return *ptr;
}

int main()
{
    fast_io;
    int t,i,j,n,ans,q;

    cin>>n>>q;
    vector<node> v(n);

    for(i=0;i<n;i++)
    {
        cin>>j;
        v[i] = node(j);
    }

    // combine( node_x, identityNode ) = node_x
    // the problem says empty subarrays are allowed
    // The minimum sum will be 0
    node identityNode(0);
    SegmentTree<node> sg(v,identityNode,combine);

    while(q--)
    {
        cin>>i>>j;
        sg.update(i-1,j);
        node as = sg.query(0,n-1);
        cout<<(as.maxSumSub)<<'\n';
    }
    return 0;
}

*/




/*

USACO


In each node of the segment tree that stores information about the range
$[l, r]$ we store the following information:
The maximum subarray sum in the range $[l, r]$. (Let this be $G$)
The maximum subarray sum in the range $[l, r]$ if it must contain $a_l$. (Let
this be $L$)
The maximum subarray sum in the range $[l, r]$ if it must contain $a_r$. (Let
this be $R$)
The total sum of the range. (Let this be $S$)

When we combine two nodes $u$ (left child) and $v$ (right child) to make node
$w$,
$w.G = \max(u.G, v.G, u.R + v.L)$
$w.L = \max(u.L, u.S + v.L)$
$w.R = \max(u.R + v.S, v.R)$
$w.S = u.S + v.S$

We can thus handle updates and queries efficiently.

*/
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;


const ll MAXN = 200001;


struct Node {

	ll g_max, l_max, r_max, sum;

	Node operator +(Node b) {

		return {

			max(max(g_max, b.g_max), r_max + b.l_max),

			max(l_max, sum + b.l_max),

			max(b.r_max, r_max + b.sum),

			sum + b.sum

		};

	}

};


ll n, a[MAXN];

Node segtree[4 * MAXN];


void build(ll l = 1, ll r = n, ll node = 1) {

	if (l == r) segtree[node] = {max(0ll, a[l]), max(0ll, a[l]), max(0ll, a[l]), a[l]};

	else {

		ll mid = (l + r) / 2;

		build(l, mid, node * 2);

		build(mid + 1, r, node * 2 + 1);

		segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];

	}

}

void update(ll pos, ll val, ll l = 1, ll r = n, ll node = 1) {

	if (l == r) segtree[node] = {max(0ll, val), max(0ll, val), max(0ll, val), val};

	else {

		ll mid = (l + r) / 2;

		if (pos > mid) update(pos, val, mid + 1, r, node * 2 + 1);

		else update(pos, val, l, mid, node * 2);

		segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];

	}

}


int main() {

	iostream::sync_with_stdio(false);

	cin.tie(0);

	ll q;

	cin >> n >> q;

	for (int i = 1; i <= n; i++) cin >> a[i];

	build();


	while (q--) {

		ll x, y;

		cin >> x >> y;

		update(x, y);

		cout << segtree[1].g_max << '\n';

	}

	return 0;

}
