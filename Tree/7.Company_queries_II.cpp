/*
Company Queries II

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

A company has n
employees, who form a tree hierarchy where each employee has a boss, except for the general director.

Your task is to process q queries of the form: who is the lowest common boss of employees a and b in the hierarchy?

Input

The first input line has two integers n and q: the number of employees and queries. The employees are numbered 1,2,…,n, and employee 1 is the general director.

The next line has n−1 integers e2,e3,…,en: for each employee 2,3,…,n their boss.

Finally, there are q lines describing the queries. Each line has two integers a and b: who is the lowest common boss of employees a and b?

Output

Print the answer for each query.

Constraints

    1≤n,q≤2⋅105


1≤ei≤i−1

1≤a,b≤n


Example

Input:
5 3
1 1 3 3
4 5
2 5
1 4

Output:
3
1
1
*/

//codeforces
// This is the classical problem of finding Lowest Common Ancestor which can be solved in multiple ways. One of the common ways is to use binary-lifting which requires   preprocessing and  

// per query.
// Code

#include<bits/stdc++.h>
using namespace std;
#define SZ 200005

int n, m, x,q,u,v;
 
 
int L[SZ]; 
vector<int> adj[SZ]; 
int jump[21][SZ];
 
void dfs(int u, int p, int l) 
{
    jump[0][u] = p;
    L[u] = l;
	
	for (int v: adj[u]) 
		if(v != p) 
		dfs(v, u, l+1);
}
 
void preprocess_LCA()
{	
	dfs(1, -1, 0);
		
	for (int i = 1; 1<<i <= n ; i++) 
	for (int j = 0; j <= n ; j++)
	jump[i][j] = jump[i-1][jump[i-1][j]];
}
 
int LCA(int p,int q)
{
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
 
 
int main()
{
    cin >> n >> q;
    for(int i = 2; i <= n; i++) {
        cin >> u;
        adj[u].push_back(i);
        adj[i].push_back(u);
    }    
    preprocess_LCA();
    while(q--) {
        cin >> u >> v;
        cout << LCA(u, v) << endl;
    }
}


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

		if((d >> i) & 1)

			x = up[x][i];

	}

	return x;

}


int LCA(int a, int b) {

	if(depth[a] < depth[b]) swap(a, b);


	a = jump(a, depth[a] - depth[b]);

	if(a == b) return a;


	R0F(i, 20) {

		int aT = up[a][i], bT = up[b][i];

		if(aT != bT) a = aT, b = bT;

	}


	return up[a][0];

}


int main() {

	re(N, Q);


	rep(N-1) {

		int b; re(b); --b;

		adj[b].pb(i+1);

	}


	up[0][0] = 0, depth[0] = 0;

	dfs(0);


	rep(Q) {

		int a, b; re(a, b); --a; --b;

		ps(LCA(a, b)+1);

	}

}
*/

/*
Alternative Solution (Company Queries II)

As mentioned in the Euler Tour Technique module, let
$\texttt{st}, \texttt{en}, \texttt{up}$ be the time-in, time-out, and ancestor
table for all nodes in the tree.

These can be filled with a DFS traversal. $\texttt{up}$ can be generated because
DFS allows the ancestors to be filled first before traversing the current node.

With this information, we can declare node $a$ an ancestor of $b$ if
$\texttt{st}[a] \le \texttt{st}[b]$ and $\texttt{en}[a] \ge \texttt{en}[b]$.

We know that if $a$ is an ancestor of $b$ or $b$ is an ancestor of $a$, the
answer will be $a$ or $b$ respectively. Otherwise, we lift one of the nodes up
(in this case, $a$) decrementally while it is not the ancestor of $b$.
Therefore, if $\texttt{up}[a][i]$ is not an ancestor of $b$, then we can set $a$
to be $\texttt{up}[a][i]$, else, we will decrement $i$ and try to find a lower
common ancestor. Afterwards, our answer is the parent of $a$.



int N, Q, T = 1;

vi st, en;

int up[200005][20];

vi adj[200005];


void dfs(int v, int p) {

	st[v] = T++;

	up[v][0] = p;


	FOR(i, 1, 20) {

		up[v][i] = up[up[v][i-1]][i-1];

	}


	for(int x : adj[v]) if(x != p) dfs(x, v);


	en[v] = T-1;

}


bool anc(int a, int b) {

	return st[a] <= st[b] && en[a] >= en[b];

}


int LCA(int a, int b) {

	if(anc(a, b)) return a;

	if(anc(b, a)) return b;


	R0F(i, 20) {

		if(!anc(up[a][i], b))

			a = up[a][i];

	}

	return up[a][0];

}


int main() {

	re(N, Q);

	st.resize(N); en.resize(N);


	rep(N-1) {

		int b; re(b); --b;

		adj[b].pb(i+1);

	}


	dfs(0,0);


	rep(Q) {

		int a, b; re(a, b); --a; --b;

		ps(LCA(a, b)+1);

	}

}

*/
/*

Alternate Solution II (Company Queries II)

We can also find the LCA of two nodes using the Tarjan's Offline LCA algorithm. By taking advantage of the DFS traversal, we can precompute the answers to the queries through forming subtrees and calculating the common parent with a similar structure as Disjoint-Set Union.

const int MX = 2e5 + 1;

	

int N, M;

vpi adj[MX], q[MX];

int fa[MX], lca[MX];

bool vis[MX];

 

int find(int u) {

	return (fa[u] == u) ? u : fa[u] = find(fa[u]);

}

 

void Tarjan(int u) {

	vis[u] = true;

 

	for (auto n : adj[u]) {

		if (vis[n.f]) continue;

 

		Tarjan(n.f);

 

		fa[n.f] = u;

	}

 

	for (auto x : q[u]) {

		if (vis[x.f])

			lca[x.s] = find(x.f);

	}

}

 

int main() {	

	setIO();

	re(N, M);

 

	F0RE(i, N) fa[i] = i;

 

	FORE(i, 2, N){

		int a; re(a);

		adj[i].pb({a, i});

		adj[a].pb({i, i});

	}

 

	F0R(i, M) {

		int a, b;

		re(a, b);

 

		q[a].pb({b, i});

		q[b].pb({a, i});

	}

 

	Tarjan(1);

 

	F0R(i, M) {

		ps(lca[i]);

	}

}

*/
