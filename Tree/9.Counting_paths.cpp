/*
Counting Paths

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

You are given a tree consisting of n
nodes, and m paths in the tree.

Your task is to calculate for each node the number of paths containing that node.

Input

The first input line contains integers n and m: the number of nodes and paths. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Finally, there are m lines describing the paths. Each line contains two integers a and b: there is a path between nodes a and b.

Output

Print n integers: for each node 1,2,…,n, the number of paths containing that node.

Constraints

    1≤n,m≤2⋅105


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
3 1 3 1 1

*/

/*

This problem can be solved using prefix sum on trees.

For every given path  

, we do following changes to the prefix array.

prefix[u]++
prefix[v]++
prefix[lca]--
prefix[parent[lca]]--

Next, we run a subtree summation over entire tree which means every node now holds the number of paths that node is a part of. This method is analogous to range update and point query in arrays, when all updates are preceded by queries.

prefix[u] = summation of (prefix[v]) for all v that are children of u*/

#include<bits/stdc++.h>
using namespace std;
#define SZ 200005

int n, m, k, x;
int L[SZ]; //L=level
vector<int> adj[SZ]; 
int jump[21][SZ];
vector<int> prefix(SZ, 0);
 
//calculates (parent,level) arrays
void dfs(int u, int p, int l) {
    jump[0][u] = p;
    L[u] = l;
	
	for (int v: adj[u]) 
		if(v != p) 
		dfs(v, u, l+1);
}
 
void preprocess_LCA() {	
	dfs(1, 0, 0);
		
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
 
void dfs_prefix_sum(int u, int p) {
	for(int v: adj[u]) {
		if(v-p) {
			dfs_prefix_sum(v, u);
			prefix[u] += prefix[v];
		}
	}
}
 
 
int main() 
{
	int u, v;
 
	cin >> n >> m;
 
	for(int i = 0; i < n-1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	preprocess_LCA();
	
	while (m--)
	{
		cin >> u >> v;
		prefix[u]++;
		prefix[v]++;
		int lca = LCA(u, v);
		prefix[lca]--;
		prefix[jump[0][lca]]--;
	}
	dfs_prefix_sum(1, 0);
 
	for(int i = 1; i <= n ; i++) 
	cout << prefix[i] << " ";
}
