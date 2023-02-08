/*
Finding a Centroid

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

Given a tree of n
nodes, your task is to find a centroid, i.e., a node such that when it is appointed the root of the tree, each subtree has at most ⌊n/2⌋ nodes.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print one integer: a centroid node. If there are several possibilities, you can choose any of them.

Constraints

    1≤n≤2⋅105


1≤a,b≤n


Example

Input:
5
1 2
2 3
3 4
3 5

Output:
3

*/

// Time Complexity: $\mathcal O(N)$

// For more information about centroids and how to find/use them, see
// their module.


#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n;  // number of nodes
vector<int> g[maxn];  // graph
int s[maxn];  // size of subtree

void dfs_size(int cur, int par) {
	s[cur] = 1;
	for (int chi : g[cur]) {
		if (chi != par) {
			dfs_size(chi, cur);
			s[cur] += s[chi];
		}
	}
}

int get_centroid(int cur, int par) {
	for (int chi : g[cur]) {
		if (chi != par) {
			if (s[chi] * 2 > n) {
				return get_centroid(chi, cur);
			}
		}
	}
	return cur;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs_size(1, -1);
	int centroid = get_centroid(1, -1);
	cout << centroid << '\n';
}


/*
Centroids

A centroid of a tree is defined as a node such that when the tree is rooted
at it, no other nodes have a subtree of size greater than $\frac{N}{2}$.

We can find a centroid in a tree by starting at the root. Each step, loop
through all of its children. If all of its children have subtree size less than
or equal to 
$\frac{N}{2}$
, then it is a centroid. Otherwise, move to the child
with a subtree size that is more than 
$\frac{N}{2}$
 and repeat until you find a
centroid.


#include <iostream>
#include <vector>

using namespace std;

const int maxn = 200010;

int n;
vector <int> adj[maxn];
int subtree_size[maxn];

int get_subtree_size(int node, int par = -1) {
	int& res = subtree_size[node];
	res = 1;
	for (int i : adj[node]) {
		if (i == par) continue;
		res += get_subtree_size(i, node);
	}
	return res;
}

int get_centroid(int node, int par = -1) {
	for (int i : adj[node]) {
		if (i == par) continue;

		if (subtree_size[i] * 2 > n) {
			return get_centroid(i, node);
		}
	}
	return node;
}

int main() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	get_subtree_size(0);
	cout << get_centroid(0) + 1 << endl;
}

Centroid Decomposition
 is a divide and conquer technique for trees.

Centroid Decomposition
 works by repeated splitting the tree and each of the
resulting subgraphs at the centroid, producing 
$\mathcal{O}(\log N)$
 layers of
subgraphs.
*/