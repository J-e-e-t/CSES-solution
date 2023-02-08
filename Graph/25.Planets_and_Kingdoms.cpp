/*
Planets and Kingdoms

A game has n planets, connected by m teleporters. Two planets a and b belong to the same kingdom exactly when there is a route both from a to b and from b to a. Your task is to determine for each planet its kingdom.

Input

The first input line has two integers n and m: the number of planets and teleporters. The planets are numbered 1,2,…,n.

After this, there are m lines describing the teleporters. Each line has two integers a and b: you can travel from planet a to planet b through a teleporter.

Output

First print an integer k: the number of kingdoms. After this, print for each planet a kingdom label between 1 and k. You can print any valid solution.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
5 6
1 2
2 3
3 1
3 4
4 5
5 4

Output:
2
1 1 1 2 2

*/

/*Time Complexity: $\mathcal O(N+M)$

Just run
Kosaraju's
or
Tarjan's
SCC algorithm on the graph.

Then assign each component an $ID$ (starting from $1$).
*/

// With Kosaraju's SCC:

#include <bits/stdc++.h>

using namespace std;


/**

 * Description: Kosaraju's Algorithm, DFS twice to generate

 	* strongly connected components in topological order. $a,b$

 	* in same component if both $a\to b$ and $b\to a$ exist.

 * Time: O(N+M)

 * Source: Wikipedia

 * Verification: POI 8 peaceful commission

*/


struct SCC {

	int N; vector<vector<int>> adj, radj;

	vector<int> todo, comp, comps; vector<bool> vis;

	void init(int _N) { N = _N;

		adj.resize(N), radj.resize(N), comp = vector<int>(N,-1), vis.resize(N);

	}

	void ae(int x, int y) {

		adj[x].push_back(y), radj[y].push_back(x);

	}

	void dfs(int x) {

		vis[x] = 1; for(int y : adj[x]) if (!vis[y]) dfs(y);

		todo.push_back(x); }

	void dfs2(int x, int v) {

		comp[x] = v;

		for(int y : radj[x]) if (comp[y] == -1) dfs2(y,v);

	}

	void gen() { // fills allComp

		for(int i=0; i<N; i++) if (!vis[i]) dfs(i);

		reverse(begin(todo), end(todo));

		for(int x : todo) if (comp[x] == -1) {

			dfs2(x,x), comps.push_back(x);

		}

	}

};


int main() {


	int n, m, a, b;

	cin >> n >> m;


	SCC graph;

	graph.init(n);

	while(m--) {

		cin >> a >> b;

		graph.ae(--a, --b);

	}

	graph.gen();


	int ID[200000]{};

	int ids = 0;

	for(int i=0; i<n; i++) {

		if(!ID[graph.comp[i]]) {

			ID[graph.comp[i]] = ++ids;

		}

	}

	cout << ids << '\n';

	for(int i=0; i<n; i++) {

		cout << ID[graph.comp[i]] << " \n"[i==n-1];

	}


}


/*
With Tarjan's SCC

#include <bits/stdc++.h>

using namespace std;


/**

 * Description: Tarjan's, DFS once to generate

 	* strongly connected components in topological order. $a,b$

 	* in same component if both $a\to b$ and $b\to a$ exist.

 	* Uses less memory than Kosaraju b/c doesn't store reverse edges.

 * Time: O(N+M)

 * Source: KACTL

 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/SCC.h

 * Verification: https://cses.fi/problemset/task/1686/

*/

/*

struct SCC {

	int N, ti = 0; vector<vector<int>> adj;

	vector<int> disc, comp, st, comps;

	void init(int _N) {

		N = _N;

		adj.resize(N), disc.resize(N), comp = vector<int>(N,-1);

	}

	void ae(int x, int y) {

		adj[x].push_back(y);

	}

	int dfs(int x) {

		int low = disc[x] = ++ti; st.push_back(x); // disc[y] != 0 -> in stack

		for(int y : adj[x]) if (comp[y] == -1) low = min(low, disc[y]?:dfs(y));

		if (low == disc[x]) { // make new SCC, pop off stack until you find x

			comps.push_back(x); for (int y = -1; y != x;)

				comp[y = st.back()] = x, st.pop_back();

		}

		return low;

	}

	void gen() {

		for(int i=0; i<N; i++) if (!disc[i]) dfs(i);

		reverse(begin(comps), end(comps));

	}

};


int main() {


	int n, m, a, b;

	cin >> n >> m;


	SCC graph;

	graph.init(n);

	while(m--) {

		cin >> a >> b;

		graph.ae(--a, --b);

	}

	graph.gen();


	int ID[200000]{};

	int ids = 0;

	for(int i=0; i<n; i++) {

		if(!ID[graph.comp[i]]) {

			ID[graph.comp[i]] = ++ids;

		}

	}

	cout << ids << '\n';

	for(int i=0; i<n; i++) {

		cout << ID[graph.comp[i]] << " \n"[i==n-1];

	}


}
*/