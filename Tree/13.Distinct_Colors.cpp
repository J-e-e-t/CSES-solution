/*
You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a color.

Your task is to determine for each node the number of distinct colors in the subtree of the node.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

The next line consists of n integers c1,c2,…,cn: the color of each node.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,…,n, the number of distinct colors.

Constraints

    1≤n≤2⋅105


1≤a,b≤n

1≤ci≤109


Example

Input:
5
2 3 2 2 1
1 2
1 3
3 4
3 5

Output:
3 1 2 1 1


Let's consider a tree rooted at node $1$, where each node has a color.

For each node, let's store a set containing only that node, and we want to merge
the sets in the nodes subtree together such that each node has a set consisting
of all colors in the nodes subtree. Doing this allows us to solve a variety of
problems, such as query the number of distinct colors in each subtree.


Naive Solution

Suppose that we want merge two sets $a$ and $b$ of sizes $n$ and $m$,
respectively. One possiblility is the following:


Better Solution

With just one additional line of code, we can significantly speed this up.

if (a.size() < b.size()) swap(a,b);

for (int x: b) a.insert(x);

Note that swap exchanges two sets in O(1)O(1) time. Thus, merging a smaller set of size mm into the larger one of size nn takes O(mlog⁡n)O(mlogn) time.

Claim: The solution runs in O(Nlog⁡2N)O(Nlog2N) time.

Proof: When merging two sets, you move from the smaller set to the larger set. If the size of the smaller set is XX, then the size of the resulting set is at least 2X2X. Thus, an element that has been moved YY times will be in a set of size at least 2Y2Y, and since the maximum size of a set is NN (the root), each element will be moved at most O(log⁡NO(logN) times.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5;

// nodes will be 1-indexed like in the problem
vector<int> adj[MAX_N + 1];

set<int> colors[MAX_N + 1];
int distinct_num[MAX_N + 1];

void process_colors(int curr, int parent) {
	for (int n : adj[curr]) {
		if (n != parent) {
			process_colors(n, curr);
			// make x the larger set always
			if (colors[curr].size() < colors[n].size()) {
				swap(colors[curr], colors[n]);
			}
			for (int item : colors[n]) {
				colors[curr].insert(item);
			}
		}
	}
	distinct_num[curr] = colors[curr].size();
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		colors[i].insert(a);
	}
	for (int i = 1; i < n; i++) {
		int a;
		int b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	process_colors(1, 0);
	for (int i = 1; i <= n; i++) {
		cout << distinct_num[i] << (i < n ? " " : "\n");
	}
}