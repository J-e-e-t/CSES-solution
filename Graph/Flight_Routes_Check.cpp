/*
There are n cities and m flight connections. Your task is to check if you can travel from any city to any other city using the available flights.

Input

The first input line has two integers n and m: the number of cities and flights. The cities are numbered 1,2,…,n.

After this, there are m lines describing the flights. Each line has two integers a and b: there is a flight from city a to city b. All flights are one-way flights.

Output

Print "YES" if all routes are possible, and "NO" otherwise. In the latter case also print two cities a and b such that you cannot travel from city a to city b. If there are several possible solutions, you can print any of them.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
4 5
1 2
2 3
3 1
1 4
3 4

Output:
NO
4 2
*/


/*
In this problem, given a directed graph with 
$n$
 nodes and 
$m$
 edges, we need to
return "YES" if we can travel between all pairs of vertices 
$u, v$
 or "NO" and
give the pair of vertices we can't travel between otherwise.

Main Idea

The theorem used here is that if one vertex can both reach and be reached by
all others, then every vertex in this graph can reach all others.

Let's say $\texttt{can[u][v]}$ is true if you can go from vertex $u$ to vertex
$v$ through a series of edges. Additionally, let's define the directed graph
given in the statement as $G$ and the reverse of it (where an edge
$u \rightarrow v$ becomes $v \rightarrow u$) as $G'$. Then, if
$\texttt{can[1][x]}$ for $1 \leq x \leq n$ in both $G$ and $G'$, the answer is
"YES".

To compute $\texttt{can[1][x]}$, we can run a dfs from from vertex $1$ and check
if you can reach vertex $x$ for all $1 \leq x \leq n$. If we can't, then print
$1$ $x$ if you're running the DFS on $G$ and $x$ $1$ otherwise.

Proof

Let's do a proof by contradiction. Assume that $\texttt{can[1][x]}$ is true for
all vertices $x$ in both $G$ and $G'$, and there exists a pair of vertices
$u, v$ such that $\texttt{can[u][v]} = \texttt{false}$. Since
$\texttt{can[1][u]}$ is true in $G'$, then $\texttt{can[u][1]}$ must be true in
$G$. Additionally, $\texttt{can[1][v]}$ must be true in $G$. So, you can travel
from $u \rightarrow 1 \rightarrow v$, which contradicts the statement that
$\texttt{can[u][v]} = \texttt{false}$. Thus, $\texttt{can[u][v]}$ is true for
all vertices $u, v$.

*/

#include <bits/stdc++.h> // see C++ Tips & Tricks
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

void setIO(string name = "") { // name is nonempty for USACO file I/O
	ios_base::sync_with_stdio(0); cin.tie(0); // see Fast Input & Output
	// alternatively, cin.tie(0)->sync_with_stdio(0);
	if (sz(name)) {
		freopen((name+".in").c_str(), "r", stdin); // see Input & Output
		freopen((name+".out").c_str(), "w", stdout);
	}
}

vi adj[100005][2]; bool vis[100005];

void dfs(int v, int x) {
	vis[v] = true;
	for (int to : adj[v][x]) {
		if (!vis[to]) {
			dfs(to, x);
		}
	}
}

int main() {
	setIO();
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		adj[u][0].pb(v);
		adj[v][1].pb(u);
	}
	dfs(0, 0);
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			cout << "NO" << '\n';
			cout << 1 << " " << i + 1 << '\n';
			return 0;
		}
	}
	memset(vis, false, sizeof(vis)); //fill vis with false
	dfs(0, 1);
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			cout << "NO" << '\n';
			cout << i + 1 << " " << 1 << '\n';
			return 0;
		}
	}
	cout << "YES" << '\n';
}

//The problem can also be solved using strongly connected components (SCC).
