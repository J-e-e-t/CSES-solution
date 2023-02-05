/*
You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a value.

Your task is to process following types of queries:

    change the value of node s

to x

calculate the sum of values in the subtree of node s


Input

The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,…,n.

The next line has n integers v1,v2,…,vn: the value of each node.

Then there are n−1 lines describing the edges. Each line contans two integers a and b: there is an edge between nodes a and b.

Finally, there are q lines describing the queries. Each query is either of the form "1 s x" or "2 s".

Output

Print the answer to each query of type 2.

Constraints

    1≤n,q≤2⋅105


1≤a,b,s≤n

1≤vi,x≤109


Example

Input:
5 3
4 2 5 2 1
1 2
1 3
3 4
3 5
2 3
1 5 3
2 3

Output:
8
10
*/

/*
This problem can be solved by flattening the tree to an array and then building a fenwick tree over flattened array.

Once reduced to an array, the problem becomes same as point update and range query. We can flatten the tree by pushing nodes to the array in the order of visiting them during a DFS.
 This ensures the entire subtree of a particular node forms a contiguous subarray in the resultant flattened array. The range of indices corresponding to subtree of a node can also be pre-calculated using a timer in DFS.
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define SZ 200005
 
int n, m, k, x, q, s;
int timer;
int start[SZ];
int endd[SZ];
int value[SZ];
int bit[SZ];
vector<int> adj[SZ]; 
 
void update(int i, int delta) {
    for(; i <= n; i += i&-i)
    bit[i] += delta;
}
 
int query(int i) {
    int sum = 0;
    for(; i > 0; i -= i&-i) 
        sum += bit[i];
    return sum;
}
 
void dfs(int u, int p) {
	start[u] = ++timer;
	update(timer, value[u]);
 
	for(int v: adj[u]){
		if(v!=p) {
			dfs(v, u);
		}
	}
	endd[u] = timer;
}
 
signed main() {
	int type;
	cin >> n >> q;
	for(int i = 1; i <=n ; i++) {
		cin >> value[i];
	}
	for(int i = 0; i < n-1; i++) {
		int u,v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs(1, 0);
 
	while (q--)
	{
		cin >> type;	
		if(type == 1) {
			cin >> s >> x;
			update(start[s], -value[s]);
			value[s] = x;
			update(start[s], +value[s]);
		}
		else {
			cin >> s;
			cout << query(endd[s]) - query(start[s] - 1) << "\n";
		}
	}
}