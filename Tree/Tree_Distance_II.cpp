/*Time Complexity: $\mathcal O(n)$

It's easy to find the sum of distances from a single node - just root the tree
at that node, do a DFS, and add the depths of each other node to the answer.
Unfortunately, $n$ can go up to $2 \cdot 10^5$, so we can't just do this for
each node.

If we have the answer for some node (let's say node 1), how can we quickly find
the answer for its neighbours?

The key observation is that if we reroot the tree at node 1's neighbour (let's
say node 2), then

The depths of all nodes in node 2's subtree decrease by 1.
The depths of all nodes outside of its subtree increase by 1.


This gives us a nice way to transition from node 1's answer to node 2's answer
using only $n$ and the size of node 2's subtree! Observe that the change in the
answer is exactly $n - 2(\text{node 2's subtree size})$.

We can use DFS to find both the answer for node 1 and the size of each node's
subtree when rooted at node 1, and then DFS again to compute all the answers.

*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
vector<int> graph[200001];
ll dp[200001], ans[200001];

void dfs1(int node = 1, int parent = 0, ll depth = 0) {
	ans[1] += depth;
	dp[node] = 1;
	for (int i : graph[node]) if (i != parent) {
		dfs1(i, node, depth + 1);
		dp[node] += dp[i];
	}
}

void dfs2(int node = 1, int parent = 0) {
	for (int i : graph[node]) if (i != parent) {
		ans[i] = ans[node] + n - 2 * dp[i];
		dfs2(i, node);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs1();
	dfs2();
	for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
	return 0;
}


/*
We can solve this problem using in-out DP on trees.
  sum of distances from u to each node in subtree rooted at u
 

sum of distances from u to each node excluding the subtree rooted at u

Now, ans[u] = in[u] + out[u]

Calculating  
is quite straightforward. Suppose we want to calculate the sum of distances starting at node u and ending at any node in subtree rooted at v. We can use the pre-calculated value for v and separately add the contribution created by edge  

. This extra quantity will be the subtree size of u. Then we can repeat the process for each child of u.

 

where v is a child of u

To calculate  
, first let's calculate the contribution of parent of u. We can use out[par] and add the difference created by the edge    

which is n-sub[par]+1. Next, we add the contribution of each sibling of u: in[sib] + sub[sib]*2.
Finally we have the following formula:

   

Code

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define SZ 200005
 
int n, m, k, x;
 
vector<int> adj[SZ];
int S[SZ];
int in[SZ];
int out[SZ];
 
void dfs_in(int u,int p)
{
	S[u] = 1;
	
	for (int v: adj[u]) {
		if (v != p) {
			dfs_in(v, u);
			S[u] += S[v];
			in[u] += in[v] + S[v];
		}
	}	
}
 
void dfs_out(int u, int p) {
	int store = 0;
	for(int v: adj[u]) {
		if(v != p)
		store += in[v] + S[v]*2;
	}
 
	for (int v : adj[u]) {
		if (v != p) {
			out[v] = (out[u] + 1*(n-S[u]+1)) + (store - (in[v] + S[v] * 2));
			dfs_out(v, u);
		}
	}
}
 
signed main() {
	int u,v;
 
	cin >> n;
	for(int i = 0; i < n-1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs_in(1, 0);
	dfs_out(1, 0);
 
	for(int i = 1; i <= n ; i++) 
		cout << in[i] + out[i] << " ";	
}

*/