/*
Pizzeria Queries

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

There are n
buildings on a street, numbered 1,2,…,n. Each building has a pizzeria and an apartment.

The pizza price in building k is pk. If you order a pizza from building a to building b, its price (with delivery) is pa+|a−b|.

Your task is to process two types of queries:

    The pizza price pk

in building k becomes x
.
You are in building k

    and want to order a pizza. What is the minimum price?

Input

The first input line has two integers n and q: the number of buildings and queries.

The second line has n integers p1,p2,…,pn: the initial pizza price in each building.

Finally, there are q lines that describe the queries. Each line is either "1 k x" or "2 k".

Output

Print the answer for each query of type 2.

Constraints

    1≤n,q≤2⋅105


1≤pi,x≤109

1≤k≤n


Example

Input:
6 3
8 6 4 5 7 5
2 2
1 5 1
2 2

Output:
5
4
*/


/*Time Complexity: $\mathcal O(N\log N)$

When we query the minimum cost to buy a pizza at point $i$, we can split it into
two cases ($i\rightarrow j$)

going downwards ($j < i$): the cost would be $p_j-j+i$
going upwards ($j > i$): the cost would be $p_j+j-i$


Since $+i$ and $-i$ are constant, we can first calculate the best cost and then
add $+i$ for the downwards cost and $-i$ for the upwards cost.

Thus, if we keep two min segtrees (one for going downwards and one for going
upwards), we can keep track of the minimum cost by setting each value in the
downwards segtree to $p_j-j$ and each value in the upwards segtree to $p_j+j$.

To query, we can simulate going downwards or upwards from position $k$. To go
downwards, we must buy pizza in the range $[1\dots k]$ so we query the minimum
cost in the range $[1\dots k]$. Going upwards is similar to going downwards, but
instead of buying pizza in the range $[1\dots k]$, we're buying pizza in the
range $[k\dots N]$; thus we query the range $[k\dots N]$ in the upwards segtree.*/

#include <bits/stdc++.h>
using namespace std;

template<class T> struct SegTree {
	T U = 1e9; T F(T a, T b) { return min(a,b); }
	int N; vector<T> t; SegTree() {}
	SegTree(int N) : N(N), t(4*N,U) {}
	void upd(int I, T V) { upd(I,V,1,1,N); }
	void upd(int I, T V, int i, int l, int r) {
		if(l==r) { t[i]=V; return; } int m=(l+r)/2;
		if(I<=m) upd(I,V,i*2,l,m);
		else upd(I,V,i*2+1,m+1,r);
		t[i] = F(t[i*2], t[i*2+1]); }
	T qry(int L, int R) { return qry(L,R,1,1,N); }
	T qry(int L, int R, int i, int l, int r) {
		if(L<=l && r<=R) return t[i];
		if(R<l || L>r) return U; int m=(l+r)/2;
		return F(qry(L,R,i*2,l,m), qry(L,R,i*2+1,m+1,r)); }
};
const int maxn = 2e5+5;

int n, q, p[maxn];
SegTree<int> down, up;

void pull(int i) {
	down.upd(i, p[i]-i);
	up.upd(i, p[i]+i);
}

int main() {

	cin >> n >> q;
	for(int i=1; i<=n; i++) cin >> p[i];

	down = up = SegTree<int>(n);
	for(int i=1; i<=n; i++) pull(i);
	while(q--) {
		int t; cin >> t;
		if(t == 1) {
			int k, x; cin >> k >> x;
			p[k] = x; pull(k);
		} else {
			int k; cin >> k;
			int D = down.qry(1,k) + k;
			int U = up.qry(k,n) - k;
			cout << min(D, U) << '\n';
		}
	}
}
