/*
Polynomial Queries

Your task is to maintain an array of n values and efficiently process the following types of queries:

    Increase the first value in range [a,b]

by 1, the second value by 2, the third value by 3
, and so on.
Calculate the sum of values in range [a,b]

    .

Input

The first input line has two integers n and q: the size of the array and the number of queries.

The next line has n values t1,t2,…,tn: the initial contents of the array.

Finally, there are q lines describing the queries. The format of each line is either "1 a b" or "2 a b".

Output

Print the answer to each sum query.

Constraints

    1≤n,q≤2⋅105


1≤ti≤106

1≤a≤b≤n


Example

Input:
5 3
4 2 3 1 7
2 1 5
1 1 5
2 1 5

Output:
17
32
*/

/*
Here's the idea: when you add a value, say  , to a segment  , the first element is incremented by  , the second by  , and so on, till the last element of the segment is incremented by  . Only, in this question  

. We'll see what happens to the prefix sum post an update:
           

Post update, in the prefix sum, the elements in the range  
stays constant. The element in the range  , with an index  , is incremented by  . And the elements in the range   are incremented by  . Similar to how multiple Fenwick trees can be used to handle range updates and range queries, we can use 6 BITs here for the update. The first will take care of  . The second will take care of constant terms. The third will take care of doubled    . The fourth will take care of doubled  . The fifth will take care of doubled constant terms. And the sixth will hold the initial prefix sum (prior to any update(s)). Notice that I've taken doubled terms because I'm splitting the terms which are being divided by   so it's possible that it no longer stays divisible by  

. Consequently, all doubled terms are halved at queries to nullify the effect. Here's the implementation, for the writing might be confusing without something concrete:
*/
#include<bits/stdc++.h>
using namespace std;

//solution:
#define int int64_t

struct fenwick {
    int n;
    vector<int> bit[6];
    fenwick(int n) {
        this -> n = n;
        for(auto& i: bit) i.assign(n + 1, 0);
    }
    fenwick(vector<int>& a): fenwick(a.size()) {
        for(int i = 1; i <= n; ++i) updatex(i, a[i - 1], 5);
    }
    int queryx(int i, int key) {
        int result = 0;
        for(int x = i; x; x -= x & -x) result += bit[key][x];
        return result;
    }
    int query(int i) {
        int a = queryx(i, 0), b = queryx(i, 1), c = queryx(i, 2);
        int d = queryx(i, 3), e = queryx(i, 4), f = queryx(i, 5);
        return a * i + b + ((c * i * i + d * i + e) / 2) + f;
    }
    int query(int lo, int hi) {
        return query(hi) - query(lo - 1);
    }
    void updatex(int i, int delta, int key) {
        for(int x = i; x <= n; x += x & -x) bit[key][x] += delta;
    }
    void updater(int lo, int hi, int delta, int key) {
        updatex(lo, delta, key);
        updatex(hi + 1, -delta, key);
    }
    void update(int lo, int hi, int delta) {
        updater(lo, hi, delta, 0); //whole idx (mid)
        updater(lo, hi, -(lo - 1) * delta, 1); //whole constant (mid)
        updater(hi + 1, n, (hi - lo + 1) * delta, 1); //whole constant (right)
        updater(lo, hi, 1, 2); //doubled idx-squared (mid)
        updater(lo, hi, -(2 * lo - 1), 3); //doubled idx (mid)
        updater(lo, hi, lo * lo - lo, 4); //doubled constant (mid)
        updater(hi + 1, n, (hi - lo) * (hi - lo + 1), 4); //doubled constant (right)
    }
};

signed main() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int& i: a) cin >> i;
    fenwick tree(a);
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            int a, b; cin >> a >> b;
            tree.update(a, b, 1);
        } else {
            int a, b; cin >> a >> b;
            cout << tree.query(a, b) << "\n";
        }
    }
    return 0;
}

/*
There is another way to solve that problem, you can use SQRT decomposition on queries.

The main idea is, you split all  
queries into        blocks, each block has       

queries.

In each block, there are some update queries and range queries. In each block, when you read an update query, you save it into a temporary vector, and when you read a range query, you iterate through all pending queries in your temporary vector, and add to your answer, based on how that update query affect your current range (intersect, outside, or inside).

After processing each block completely, you have to update the whole array, so your array will be ready for the next blocks of query.

This solution doesn't need any advanced data structures like Fenwick Tree or Segment Tree, just an array of prefix sum is enough.

About the complexity, you may have some observation:

    In each block, the complexity to solve each block is at most      

, i.e the number of update queries times the number of range queries. Because of AM-GM inequality, it will not exceed     

.

And after each block, you have to update the whole array in  

    .

Then, the final complexity is       

, which is enough for the problem constraint.

You can see my code for more detail : https://hastebin.com/ogerunavit.cpp
*/



/*

https://www.youtube.com/watch?v=z-mL6NShNbk


#include<bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

#define int long long
#define pll pair<long long,long long>

#define in(x) long long x;cin>>x
#define pb push_back
#define F first
#define S second
#define endl "\n"

#define test() int t;cin>>t;while(t--)
#define KStest() int t,t1;cin>>t;t1=t;while(t--)
#define KScout cout<<"Case #"<<t1-t<<": "
#define deb(x) cout<<#x<<" "<<x<<endl;
#define setbits __builtin_popcountll

const long long mod = 1e9 + 7;
const int MAX = INT_MAX;
const long long inf = LLONG_MAX;
const double pi = 3.14159265358979323846;

int dirX[] = {1, -1, 0, 0};
int dirY[] = {0, 0, 1, -1};

using namespace std;
void print_bool(bool zeman_modnar)
{
	if (zeman_modnar)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}
// template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//order_of_key   ==> number of elements whose value is less than the given element
//find_by_order ==> kth element in the set (counting from 0)


int helper(int n)
{
	return (n * (n + 1)) / 2;
}

struct Segment_Tree {
	vector<int> segtree;
	vector<int> lazy1, lazy2;

	Segment_Tree(vector<int> &a) {
		int n = a.size();
		segtree = vector<int>(4 * n);
		lazy1 =  vector<int>(4 * n, 0);
		lazy2 = vector<int>(4 * n, 0);
		build(a, 0, n - 1, 1);
	}

	int f(int a, int b) {
		//Just change this for a different segment tree
		return a + b;
	}

	void build(vector<int> &a, int s, int e, int root) {
		// base case
		if (s == e) {
			segtree[root] = a[s];
			return;
		}

		int mid = (s + e) / 2;
		build(a, s, mid, 2 * root);
		build(a, mid + 1, e, 2 * root + 1);

		// self work
		segtree[root] = f(segtree[2 * root], segtree[2 * root + 1]);
	}

	void propagate(int root, int s, int e)
	{
		if (lazy1[root] != 0)
		{
			int width = (e - s + 1);
			segtree[root] += (helper(width - 1) * lazy2[root]);
			int rem = (width * lazy1[root] );
			segtree[root] += rem;

			int mid = (s + e) / 2;
			if (s != e)
			{
				lazy1[2 * root] += lazy1[root];
				lazy1[2 * root + 1] += (lazy1[root] + (mid - s + 1) * lazy2[root]);
				lazy2[2 * root] += lazy2[root];
				lazy2[2 * root + 1] += lazy2[root];
			}
			lazy1[root] = 0;
			lazy2[root] = 0;
		}
	}

	void rupd(int s, int e, int root, int l, int r)
	{
		propagate(root, s, e);

		if (s > r || e < l)
			return;

		if (s >= l && e <= r)
		{
			int mid = (s + e) / 2;
			int width = e - s + 1;
			int left = s - l + 1;
			int right = e - l + 1;

			segtree[root] += helper(right);
			segtree[root] -= helper(left - 1);

			int rightstart = left + (mid - s + 1);
			if (s != e)
			{
				lazy2[2 * root] ++;
				lazy2[2 * root + 1]++;
				lazy1[2 * root] += left;
				lazy1[2 * root + 1] += rightstart;
			}
			return;
		}

		int mid = (s + e) / 2;

		rupd(s, mid, 2 * root, l, r);
		rupd(mid + 1, e, 2 * root + 1, l, r);
		segtree[root] = f(segtree[2 * root], segtree[2 * root + 1]);
	}

	int query(int s, int e, int root, int l, int r) {  //query with root index set to 1
		// completely out of range
		propagate(root, s, e);
		if (s > r || e < l) {
			return 0;
		}
		// completely in range
		if (s >= l && e <= r) {
			return segtree[root];
		}
		// partial overlap
		int mid = (s + e) / 2;
		int x = query(s, mid, 2 * root, l, r);
		int y = query(mid + 1, e, 2 * root + 1, l, r);
		return f(x, y);
	}
};

int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	in(n); in(q);
	vector<int> v(n);

	for (int i = 0; i < n; i++)
		cin >> v[i];

	Segment_Tree segtree(v);

	while (q--)
	{
		in(t); in(a); in(b);
		if (t == 1)
		{
			segtree.rupd(0, n - 1, 1, a - 1, b - 1);
		}
		else
		{
			cout << segtree.query(0, n - 1, 1, a - 1, b - 1) << endl;
		}
	}
	return 0;
}*/