/*
Distance Queries

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

You are given a tree consisting of n
nodes.

Your task is to process q queries of the form: what is the distance between nodes a and b?

Input

The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Finally, there are q lines describing the queries. Each line contains two integer a and b: what is the distance between nodes a and b?

Output

Print q integers: the answer to each query.

Constraints

    1≤n,q≤2⋅105


1≤a,b≤n


Example

Input:
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4

Output:
1
3
2
*/


// codeforces
// Distance between node u and v can be calculated as  .
// LCA of (u,v) can be calculated using binary-lifting approach in  

// per query.
// Code

#include<bits/stdc++.h>
using namespace std;
#define SZ 200005
 
int n, m, k, x;
int L[SZ]; //level-array
vector<int> adj[SZ]; 
int jump[21][SZ];
 
void dfs(int u, int p, int l) {
    jump[0][u] = p;
    L[u] = l;
	
	for (int v: adj[u]) 
		if(v != p) 
		dfs(v, u, l+1);
}
 
void preprocess_LCA() {	
	dfs(1, -1, 0);
		
	for (int i = 1; 1<<i <= n ; i++) 
	for (int j = 0; j <= n ; j++)
	jump[i][j] = jump[i-1][jump[i-1][j]];
}
 
int LCA(int p,int q) {
	if(L[p] < L[q])
	swap(p, q);
	
	int diff = L[p] - L[q];
	
	for(int i = 20; i >= 0; i--) 
		if(diff & (1<<i)) 
		p = jump[i][p];
		
	if(p == q) return p;
 
	for (int i = 20; i >= 0; i--) {
		if (jump[i][p] != jump[i][q]) {
			p = jump[i][p];
			q = jump[i][q];
		}
	}
	return jump[0][p];
}
 
int main() {
	int u, v, q, a, b;
	cin >> n >> q;
	for(int i = 0; i < n-1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	preprocess_LCA();
 
	while(q--) {
		cin >> a >> b;
		int lca = LCA(a,b);
		cout << L[a] + L[b] - 2*L[lca] << endl;
	}
}


// Find LCA of node $a$ and $b$ as described above. Then, the distance between the
// two nodes would be the
// $\texttt{depth}[a] + \texttt{depth}[b] - 2 \cdot \texttt{depth}[\textrm{lca}(a, b)]$.


/*
int N, Q, T = 1;

int depth[200005];

int up[200005][20];

vi adj[200005];


void dfs(int v) {

	FOR(i, 1, 20) {

		up[v][i] = up[up[v][i-1]][i-1];

	}


	for(int x : adj[v]) {

		if(x != up[v][0]) {

			depth[x] = depth[up[x][0] = v]+1;

			dfs(x);

		}

	}

}


int jump(int x, int d) {

	F0R(i, 20) {

		if((d>>i)&1)

			x = up[x][i];

	}

	return x;

}


int LCA(int a, int b) {

	if(depth[a] < depth[b]) swap(a, b);


	a = jump(a, depth[a] - depth[b]);

	if(a == b) return a;


	R0F(i, 20) {

		int aT = up[a][i]; int bT = up[b][i];

		if(aT != bT) a = aT, b = bT;

	}


	return up[a][0];

}


int main() {

	re(N, Q);


	rep(N-1) {

		int a, b; re(a, b); --a,--b;

		adj[b].pb(a);

		adj[a].pb(b);

	}


	up[0][0] = 0, depth[0] = 0;

	dfs(0);


	rep(Q) {

		int a, b; re(a, b); --a; --b;

		ps(depth[a] + depth[b] - 2 * depth[lca(a, b)]);

	}

}
*/
