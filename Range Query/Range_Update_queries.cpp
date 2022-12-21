/*
Given an array of n integers, your task is to process q queries of the following types:

    increase each value in range [a,b]

by u

what is the value at position k

    ?

Input

The first input line has two integers n and q: the number of values and queries.

The second line has n integers x1,x2,…,xn: the array values.

Finally, there are q lines describing the queries. Each line has three integers: either "1 a b u" or "2 k".

Output

Print the result of each query of type 2.

Constraints

    1≤n,q≤2⋅105


1≤xi,u≤109

1≤k≤n

1≤a≤b≤n


Example

Input:
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4

Output:
5
6
*/

/*

Explanation
Implementation Note

We will be using 1-based arrays (index starting from 1) throughout this problem. The element at index 0 will always be 0.

We can solve this problem by taking advantage of a difference array, where diff[i]=arr[i]−arr[i−1]diff[i]=arr[i]−arr[i−1] for all ii (1≤i≤n)(1≤i≤n). To calculate arr[i]arr[i] using diffdiff, we can find the sum of all the values in diffdiff up to the ii-th index:
arr[i]=∑j=0idiff[j]=diff[0]+diff[1]+⋯+diff[i]
arr[i]=j=0∑i​diff[j]=diff[0]+diff[1]+⋯+diff[i]

This means that we can answer point queries in O(log⁡n)O(logn) time by calculating prefix sums of diffdiff with a segment tree or binary-indexed tree.

To respond to range updates on an interval [a,b][a,b], we can increment diff[a]diff[a] by uu and decrement diff[b+1]diff[b+1] by uu. This way, when answering point queries, all the values at indices a…ba…b will be increased by uu and all values at indices less than aa or greater than bb remain unchanged.
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

template<class T> struct Seg {
	int n;
	T ID = 0;
	vector<T> seg;
	T comb (T a, T b) {return a + b;}
	void init (int _n) {n = _n; seg.assign(n * 2, ID);}
	void pull (int p) {
		seg[p] = comb(seg[p * 2], seg[p * 2 + 1]);
	}
	void upd (int i, T val) {
		seg[i+=n] += val;
		for (i /= 2; i; i /= 2) {
			pull(i);
		}
	}
	T query (int l, int r) {
		T ra = ID, rb = ID;
		for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra, seg[l++]);
			if (r&1) rb = comb(rb, seg[--r]);
		}
		return comb(ra, rb);
	}
};

int main () {
	int n, q;
	cin >> n >> q;
	// sgt stores the difference array
	Seg<ll> sgt;
	sgt.init(n + 1);
	vector<int> ar(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> ar[i];
		sgt.upd(i, ar[i] - ar[i - 1]);
	}
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int a, b;
			ll val;
			cin >> a >> b >> val;
			sgt.upd(a, val);
			sgt.upd(b + 1, -val);
		} else {
			int k;
			cin >> k;
			cout << sgt.query(1, k) << '\n';
		}
	}
}
