/*
Path Queries

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

You are given a rooted tree consisting of n
nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a value.

Your task is to process following types of queries:

    change the value of node s

to x

calculate the sum of values on the path from the root to node s


Input

The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,…,n.

The next line has n integers v1,v2,…,vn: the value of each node.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Finally, there are q lines describing the queries. Each query is either of the form "1 s x" or "2 s".

Output

Print the answer to each query of type 2.

Constraints

    1≤n,q≤2⋅105


1≤a,b,s≤n

1≤vi,x≤109


Example

Input:
5 3
4 2 5 2 1
1 2
1 3
3 4
3 5
2 4
1 3 2
2 4

Output:
11
8
*/

/*
This problem can be solved using Heavy-Light decomposition of trees.

First, we decompose the tree into chains using heavy-light scheme and then build a segment tree over each chain. A path from node u to v can seen as concatenation of these chains and each query can be answered by querying the segment trees corresponding to each of these chains on the path. Since heavy-light scheme ensures there can be at most  
chains, each query can be answered in    

time.

Similarly, each update can be performed in  
time as it requires update on a single chain (single segment tree) corresponding to the given node.

*/

#include<bits/stdc++.h>
using namespace std;
#define int long long int
 
const int N = 200005;
 
struct node {  
		int l, r, mx;
		node *left, *right;
		node(int ll, int rr) : 
			l(ll), r(rr), mx(0), left(NULL), right(NULL) {}
}* root[N];
vector<int> chain[N];
vector<int> adj[N];
 
int sz[N], H[N], P[N], chainHd[N], pos[N],leadingEdge[N];
 
 
void update(node* p,int idx, int val) {
	if(p->l == p->r) {
		p->mx = val;
		return;
	}        
	int mid = (p->l + p->r)>>1;
	update(idx<=mid ? p->left : p->right, idx, val);
	p->mx = (p->left->mx + p->right->mx);
}
 
int query(node* p,int ql, int qr) {
	if(qr < p->l or p->r < ql) return 0;
	if(ql <= p->l and p->r <= qr) return p->mx;
	return query(p->left,ql, qr) + query(p->right,ql,qr);
}
		
node* build(int n,int l, int r) {
	node *p = new node(l, r);
	if(l < r) {
		int mid = (l + r)>>1;
		p->left = build(n,l, mid);
		p->right = build(n,mid+1, r);
	}
	p->mx= (l==r) ? leadingEdge[chain[n][l]] : (p->left->mx + p->right->mx);
	return p;
}
 
void dfs_build(int n, int p, int h) {   
	P[n] = p;
	H[n] = h;
	sz[n] = 1;
	for(int i=0; i<adj[n].size() ; i++) {
		int v=adj[n][i];
		if(v-p){
		 dfs_build(v, n, h+1);
		 sz[n] += sz[v];
		}
	}
}
 
void HLD(int n) {
	chain[n].push_back(n);
	for(int i = 0; i < chain[n].size();i++){
		int v = chain[n][i];
		chainHd[v] = n;
		pos[v] = i;
		for( int k=0;k<adj[v].size();k++) {
			int j=adj[v][k];
			if(j!=P[v]) 
			(sz[j]<<1) >= sz[v] ? chain[n].push_back(j) : HLD(j);
		}
	}
	root[n] = build(n,0, chain[n].size() -1);
}
 
int HLDquery(int u, int v) {
	int ans = 0;
	while(chainHd[u] != chainHd[v]) {
		if(H[chainHd[u]] > H[chainHd[v]]) swap(u, v);
		ans += query(root[chainHd[v]],0, pos[v]);
		
		v = P[chainHd[v]];
	}
	if(pos[u] > pos[v]) 
	swap(u, v);
	ans += query(root[chainHd[u]],pos[u], pos[v]);
	return ans;
}
 
signed main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int q, n, a, b, c, k, ti, type;
 
	cin >> n >> q;
	for(int i = 1; i <= n ; i++) {
		cin >> leadingEdge[i];
	}
 
	for(int i = 0; i < n-1; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs_build(1,1,0);
	HLD(1);
			
	while (q--)
	{
		int type;
		cin >> type;
		
		if(type==1)
		{
			cin >> k >> ti;
			update(root[ chainHd[k] ], pos[k] , ti);
		}
		else
		{
			cin >> k;
			cout <<  HLDquery(1,k) << endl;
		}
	}
}

/*
Explanation: CPH 18.2

Unlike the above explanation, instead of storing the subtree size, we store the
right index of the subtree in order to determine the bounds of each node's
subtree.

Notice that when we update a node with value $A[s]$ to $x$, the root-to-node sum
for each node in its subtree increases by the difference $x-A[s]$. Using ETT,
this is equivalent to a range update.

We can use a Fenwick tree which supports range increment/decrements and point
queries in $\mathcal{O}(\log N)$ time.

When implementing your solution, recall that incrementing a range $[a, b]$ with
a Fenwick tree corresponds to the operations

$$\text{upd}(a, x)$$

$$\text{upd}(b+1, -x)$$

Time Complexity: $\mathcal O((N+Q)\log N)$


/**

 * Author: Lukas Polacek

 * Date: 2009-10-30

 * License: CC0

 * Source: folklore/TopCoder

 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1],

 * and updates single elements a[i],

 * taking the difference between the old and new value.

 * Time: Both operations are $O(\log N)$.

 * Status: Stress-tested

 */


/*
struct FT {

	vector<ll> s;

	FT(int n) : s(n) {}

	void update(int pos, ll dif) { // a[pos] += dif

		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;

	}

	ll query(int pos) { // sum of values in [0, pos)

		ll res = 0;

		for (; pos > 0; pos &= pos - 1) res += s[pos-1];

		return res;

	}

};



const int mx = 2e5+1;


vi adj[mx];

int A[mx];

int st[mx];

int en[mx];

int timer = 0;

FT ft(mx+1);


void dfs(int x, int p) { // euler tour

	st[x] = timer++;

	for(const int &e : adj[x]) if(e != p) dfs(e, x);

	en[x] = timer-1;

}


int main() {

	setIO();


	int n, q;

	cin >> n >> q;


	for(int i = 1; i <= n; i++) cin >> A[i];


	for(int i = 0; i < n-1; i++) {

		int a, b; cin >> a >> b;

		adj[a].pb(b);

		adj[b].pb(a);

	}


	dfs(1, 0);


	for(int i = 1; i <= n; i++) {

		ft.update(st[i], A[i]);

		ft.update(en[i]+1, -A[i]);

	}


	for(int i = 0; i < q; i++) {

		int type, s; cin >> type >> s;

		if(type == 1) {

			int x; cin >> x;

			ft.update(st[s], x-A[s]);

			ft.update(en[s]+1, -(x-A[s])); // increment by 1

			A[s] = x;

		} else {

			cout << ft.query(st[s]+1) << '\n';

		}

	}

}

*/