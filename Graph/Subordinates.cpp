/*
Given the structure of a company, your task is to calculate for each employee the number of their subordinates.

Input

The first input line has an integer n: the number of employees. The employees are numbered 1,2,…,n, and employee 1 is the general director of the company.

After this, there are n−1 integers: for each employee 2,3,…,n their direct boss in the company.

Output

Print n integers: for each employee 1,2,…,n the number of their subordinates.

Constraints

    1≤n≤2⋅105


Example

Input:
5
1 1 2 3

Output:
4 1 1 0 0
*/

#include <bits/stdc++.h>
using namespace std;

const int SZ = 2e5;

vector<int> children[SZ];
int subtree_size[SZ], depth[SZ];

void dfs_size(int node) {
	subtree_size[node] = 1; // This one represents the root of `node's` subtree
	// (which would be `node` itself)
	for (int child : children[node]) {
		depth[child] = depth[node]+1; // not needed for this problem
		dfs_size(child);
		subtree_size[node] += subtree_size[child];
		// Add `node's` children's subtrees to the size of `node's` subtree
	}
}

int main() {
	int N; cin >> N;
	for(int i = 1; i < N; i++) {
		int parent; cin >> parent; parent--;
		// this node is the parent of node i ... Also notice
		// the decrement operator in order to make the node 0-indexed
		children[parent].push_back(i);
	}
	dfs_size(0);
	for(int i = 0; i < N; i++) {
		cout << subtree_size[i]-1;
		if(i != N-1) cout << " ";
	}
	cout << "\n";
}