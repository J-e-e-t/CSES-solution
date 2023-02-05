/*
Hotel Queries

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

There are n
hotels on a street. For each hotel you know the number of free rooms. Your task is to assign hotel rooms for groups of tourists. All members of a group want to stay in the same hotel.

The groups will come to you one after another, and you know for each group the number of rooms it requires. You always assign a group to the first hotel having enough rooms. After this, the number of free rooms in the hotel decreases.

Input

The first input line contains two integers n and m: the number of hotels and the number of groups. The hotels are numbered 1,2,…,n.

The next line contains n integers h1,h2,…,hn: the number of free rooms in each hotel.

The last line contains m integers r1,r2,…,rm: the number of rooms each group requires.

Output

Print the assigned hotel for each group. If a group cannot be assigned a hotel, print 0 instead.

Constraints

    1≤n,m≤2⋅105


1≤hi≤109

1≤ri≤109


Example

Input:
8 5
3 2 4 1 5 5 2 6
4 4 7 1 1

Output:
3 5 0 1 1
*/

/*
Walking on a Segment Tree

You want to support queries of the following form on an array $a_1,\ldots,a_N$
(along with point updates).

Find the first $i$ such that $a_i\ge x$.


Of course, you can do this in $\mathcal{O}(\log^2N)$ time with a max segment
tree and binary searching on the first $i$ such that
$\max(a_1,\ldots,a_i)\ge x$. But try to do this in $\mathcal{O}(\log N)$ time.

Instead of binary searching and querying the segment tree separately, let's do
them together!
Assume that you know that the answer is in some range $[l, r]$. Let
$mid = \left \lfloor{\frac{l + r}{2}}\right \rfloor$.
If $\max(a_l, \dots, a_{mid}) \geq x$, then we know that the answer is in the
range $[l, mid]$. Otherwise, the answer is in the range $[mid + 1, r]$.
Imagine that the segment tree is a decision tree. We start at the root and move
down. When we're at some node that contains $\max(a_l, \dots, a_r)$ and we know
that the answer is in the range $[l, r]$, we move to the left child if
$\max(a_l, \dots, a_{mid}) \geq x$; otherwise, we move to the right child.
This is convenient because $\max(a_l, \dots, a_{mid})$ is already stored in the
left child, so we can find it in $\mathcal{O}(1)$ time.


*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

int n;
int segtree[4 * MAXN], a[MAXN];

void build(int l = 1, int r = n, int node = 1) {
	if (l == r) segtree[node] = a[l];
	else {
		int mid = (l + r) / 2;
		build(l, mid, node * 2);
		build(mid + 1, r, node * 2 + 1);
		segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
	}
}

void queryupdate(int val, int l = 1, int r = n, int node = 1) {
	if (l == r) {
		segtree[node] -= val;
		cout << l << ' ';
	} else {
		int mid = (l + r) / 2;
		if (segtree[node * 2] >= val) queryupdate(val, l, mid, node * 2);
		else queryupdate(val, mid + 1, r, node * 2 + 1);

		segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
	}
}

int main() {
	iostream::sync_with_stdio(false);
	cin.tie(0);
	int q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	build();

	while (q--) {
		int x;
		cin >> x;
		if (segtree[1] < x) cout << "0 ";
		else queryupdate(x);
	}
	return 0;
}