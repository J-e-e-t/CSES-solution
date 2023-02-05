/*
Increasing Array Queries

You are given an array that consists of n integers. The array elements are indexed 1,2,…,n.

You can modify the array using the following operation: choose an array element and increase its value by one.

Your task is to process q queries of the form: when we consider a subarray from position a to position b, what is the minimum number of operations after which the subarray is increasing?

An array is increasing if each element is greater than or equal with the previous element.

Input

The first input line has two integers n and q: the size of the array and the number of queries.

The next line has n integers x1,x2,…,xn: the contents of the array.

Finally, there are q lines that describe the queries. Each line has two integers a and b: the starting and ending position of a subarray.

Output

For each query, print the minimum number of operations.

Constraints

    1≤n,q≤2⋅105


1≤xi≤109

1≤a≤b≤n


Example

Input:
5 3
2 10 4 2 5
3 5
2 2
1 4

Output:
2
0
14
*/


/*
Time Complexity: $\mathcal O((N + Q) \log N)$.

In this problem, we can answer the queries offline (i.e. read in the queries and
process them in a different order). More specifically, we process queries in
order of their left endpoints.

First, let's think about how we'd answer a single query $(l, r)$. Consider the
following algorithm:

Let $\texttt{mx}_0 = 0$ and $j = 0$.
For each $i$ in $[l, r]$:

If $x_i > \texttt{mx}_j$, then set $\texttt{mx}_{j + 1} = x_i$ and increment
$j$.
Otherwise, add $\texttt{mx}_j - x_i$ to the answer.




Notice how each $\texttt{mx}_j$ (except the last) contributes a fixed amount to
the answer, regardless of $r$. If $\texttt{pref}$ is the prefix sum array of $x$
and $\texttt{idx}_j$ is the index of $\texttt{mx}_j$ in $x$, then this amount is

$$(\texttt{idx}_{j + 1} - 1 - \texttt{idx}_j) \cdot \texttt{mx}_j - (\texttt{pref}_{\texttt{idx}_{j + 1} - 1} - \texttt{pref}_{\texttt{idx}_j})$$

This means that for a fixed $l$, we can compute each $\texttt{mx}_j$ and their
contributions, and then use std::upper_bound and a BIT to answer queries with
variable $r$!

If we want to change $l$, notice how we can update $\texttt{mx}$ efficiently by
using a monotone stack. Since each $\texttt{mx}_j$'s contribution depends on
$x_i$ after it, the contributions of the old $\texttt{mx}_j$ don't change.

Again, we use std::upper_bound and a BIT to answer queries.
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

int n, q;
ll x[200002], pref[200002], ans[200002];
ll contrib[200002], bit[200002];
vector<pair<int, int>> bckt[200001];

void update(int pos, ll val) { for (; pos <= n; pos += pos & -pos) bit[pos] += val; }

ll query(int a, int b) {
	ll ans = 0;
	for (; b; b -= b & -b) ans += bit[b];
	for (a--; a; a -= a & -a) ans -= bit[a];
	return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		pref[i] = pref[i - 1] + x[i];
	}
	x[n + 1] = INF;
	pref[n + 1] = pref[n] + x[n + 1];
	for (int i = 1; i <= q; i++) {
		int a, b;
		cin >> a >> b;
		bckt[a].push_back({b, i});
	}
	deque<int> stck = {n + 1};
	for (int i = n; i; i--) {
		while (stck.size() && x[i] >= x[stck.front()]) {
			update(stck.front(), -contrib[stck.front()]);
			stck.pop_front();
		}
		contrib[i] = (stck.front() - 1 - i) * x[i] - (pref[stck.front() - 1] - pref[i]);
		update(i, contrib[i]);
		stck.push_front(i);
		for (pair<int, int> j : bckt[i]) {
			int pos = upper_bound(stck.begin(), stck.end(), j.first) - stck.begin() - 1;
			ans[j.second] = (pos ? query(i, stck[pos - 1]) : 0) + (j.first - stck[pos]) * x[stck[pos]] - (pref[j.first] - pref[stck[pos]]);
		}
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}