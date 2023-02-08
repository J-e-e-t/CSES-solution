/*
Fixed-Length Paths I

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

Given a tree of n
nodes, your task is to count the number of distinct paths that consist of exactly k edges.

Input

The first input line contains two integers n and k: the number of nodes and the path length. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print one integer: the number of paths.

Constraints

    1≤k≤n≤2⋅105


1≤a,b≤n


Example

Input:
5 2
1 2
2 3
3 4
3 5

Output:
4
*/

/*
Time Complexity: $\mathcal O(N \log N)$

Given a node $u$, we know that any path in the tree either passes $u$ or is
completely contained in one of $u$'s children's subtrees. This means that to
solve the problem on a tree containing $u$, we can:

Count the number of paths of length $k$ that pass through $u$.
Remove $u$ and its incident edges from the tree.
Recursively solve the problem on the new trees that are formed.

Counting paths through $u$

We can count the number of paths passing through $u$ in a tree of size $M$ in
$\mathcal O(M)$ time.

We process each of $u$'s children's subtrees in order. Let $\texttt{cnt}_i[d]$
be the number of nodes we've visited with depth $d$ after processing the first
$i$ of $u$'s children's subtrees. A node with depth $d$ in $u$'s $i$-th child's
subtree will contribute $\texttt{cnt}_{i - 1}[k - d]$ paths to the answer.

Using two DFSes for each child, we can calculate its contribution and then
update $\texttt{cnt}$ in $\mathcal O(M)$ time total.

Applying centroid decomposition

We can combine the previous idea with centroid decomposition
to solve the whole problem in $\mathcal O(N \log N)$ time.

When processing some tree, simply let the $u$ we use be that tree's centroid.
Since the centroid tree has a depth of $\mathcal O(\log N)$ and each layer in
the centroid tree takes amortized $\mathcal O(N)$ time to process, the total
complexity is $\mathcal O(N \log N)$.

*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k;
vector<int> graph[200001];
int subtree[200001];

ll ans = 0;
int cnt[200001]{1}, mx_depth;
bool processed[200001];

int get_subtree_sizes(int node, int parent = 0) {
	subtree[node] = 1;
	for (int i : graph[node]) if (!processed[i] && i != parent)
		subtree[node] += get_subtree_sizes(i, node);
	return subtree[node];
}

int get_centroid(int desired, int node, int parent = 0) {
	for (int i : graph[node])
		if (!processed[i] && i != parent && subtree[i] >= desired)
			return get_centroid(desired, i, node);
	return node;
}

void get_cnt(int node, int parent, bool filling, int depth = 1) {
	if (depth > k) return;
	mx_depth = max(mx_depth, depth);
	if (filling) cnt[depth]++;
	else ans += cnt[k - depth];
	for (int i : graph[node]) if (!processed[i] && i != parent)
		get_cnt(i, node, filling, depth + 1);
}

void centroid_decomp(int node = 1) {
	int centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
	processed[centroid] = true;
	mx_depth = 0;
	for (int i : graph[centroid]) if (!processed[i]) {
		get_cnt(i, centroid, false);
		get_cnt(i, centroid, true);
	}
	fill(cnt + 1, cnt + mx_depth + 1, 0);
	for (int i : graph[centroid]) if (!processed[i]) centroid_decomp(i);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	centroid_decomp();
	cout << ans;
	return 0;
}