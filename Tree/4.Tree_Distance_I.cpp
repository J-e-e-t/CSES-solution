/*
You are given a tree consisting of n nodes.

Your task is to determine for each node the maximum distance to another node.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,…,n, the maximum distance to another node.

Constraints

    1≤n≤2⋅105


1≤a,b≤n


Example

Input:
5
1 2
1 3
3 4
3 5

Output:
2 3 2 3 3
*/

//Solution 1

// Compute a diameter of the tree as described by algorithm 2
// here. Once we have a diameter $(a,b)$,
// output $\max(dist(a,i),dist(b,i))$ for each node $i$.

#include <bits/stdc++.h>

using namespace std;

// dist[0][i] = distance from node a to node i
// dist[1][i] = distance from node b to node i
int dist[2][200000];
vector<int> adj[200000];

int dfs(int u, int p, int d, int i) {
	dist[i][u] = d;
	int opt = -1;
	for (int v : adj[u]) {
		if (v != p) {
			int x = dfs(v, u, d+1, i);
			if (opt == -1 || dist[i][x] > dist[i][opt]) opt = x;
		}
	}
	return opt == -1 ? u : opt;
}

int main() {
	int n; cin >> n;
	for (int i = 0; i < n-1; i++) {
		int a, b; cin >> a >> b; --a; --b;
		adj[a].push_back(b); adj[b].push_back(a);
	}
	// first, find node a by finding the farthest node from an arbitrary node x
	int mxNode = dfs(0, 0, 0, 0);
	// then, find node b (this step also computes distance from a to every other node)
	int mxNode2 = dfs(mxNode, mxNode, 0, 0);
	// finally, compute the distance from b to every other node
	dfs(mxNode2, mxNode2, 0, 1);

	for (int i = 0; i < n; i++) {
		cout << max(dist[0][i], dist[1][i]) << " \n"[i == n-1];
	}
	return 0;
}

// Solution 2
/*

#include<bits/stdc++.h>

using namespace std;


vector<int> adj[200001];

int firstMax[200001];  // to store first-max length.

int secondMax[200001];  // to store second-max length.

int c[200001];   // to store child for path of max length.


// calculate for every node x the maximum

// length of a path that goes through a child of x

void dfs(int v, int p) {

	firstMax[v] = 0;

	secondMax[v] = 0;

	for (auto x : adj[v]) {

		if (x == p)continue;

		dfs(x, v);

		if (firstMax[x] + 1 > firstMax[v]) {

			secondMax[v] = firstMax[v];

			firstMax[v] = firstMax[x] + 1;

			c[v] = x;

		}

		else if (firstMax[x] + 1 > secondMax[v]) {

			secondMax[v] = firstMax[x] + 1;

		}

	}

}


// calculate for every node x the

// maximum length of a path through its parent p

void dfs2(int v, int p) {

	for (auto x : adj[v]) {

		if (x == p) continue;

		if (c[v] == x) {

			if (firstMax[x] < secondMax[v] + 1) {

				secondMax[x] = firstMax[x];

				firstMax[x] = secondMax[v] + 1;

				c[x] = v;

			}

			else {

				secondMax[x] = max(secondMax[x], secondMax[v] + 1);

			}

		}

		else {

			secondMax[x] = firstMax[x];

			firstMax[x] =  firstMax[v] + 1;

			c[x] = v;

		}

		dfs2(x, v);

	}

}


int main() {

	FIO;

	int n, u, v;

	cin >> n;

	for (int i = 0; i < n - 1; i++) {

		cin >> u >> v;

		adj[u].push_back(v);

		adj[v].push_back(u);

	}

	dfs(1, -1);

	dfs2(1, -1);


	for (int i = 1; i <= n; i++) {

		cout << firstMax[i] << " ";

	}

	return 0;

}


*/