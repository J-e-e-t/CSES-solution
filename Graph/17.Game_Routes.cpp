/*
A game has n levels, connected by m teleporters, and your task is to get from level 1 to level n. The game has been designed so that there are no directed cycles in the underlying graph. In how many ways can you complete the game?

Input

The first input line has two integers n and m: the number of levels and teleporters. The levels are numbered 1,2,…,n.

After this, there are m lines describing the teleporters. Each line has two integers a and b: there is a teleporter from level a to level b.

Output

Print one integer: the number of ways you can complete the game. Since the result may be large, print it modulo 109+7.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
4 5
1 2
2 4
1 3
3 4
1 4

Output:
3
*/

// Time Complexity: $\mathcal{O}(N+M)$

// This problem is very similar to the "Longest Flight Route" problem discussed
// earlier in this module. Let $dp[v]$ denote the number of paths reaching $v$. We
// can see,

// $$dp[v]= \sum_{\text{edge } u\to v \text{ exists}}dp[u],$$

// with an exception of $dp[1]$, or the starting node, having a value of 1. We
// process the nodes topologically so $dp[u]$ will already have been computed
// before $dp[v]$.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n;
vector<int> edge[100001];
vector<int> backedge[100001];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int m; cin >> n >> m;
	int in_degree[n+1], dp[n+1];
	for(int i = 0; i <= n; i++){
		in_degree[i] = 0;
		dp[i] = 0;
	}
	dp[1] = 1;
	for(int i = 0; i < m; i++){
		int a,b; cin >> a >> b;
		edge[a].push_back(b);
		backedge[b].push_back(a);
		in_degree[b]++;
	}
	//uses Kahn's algorithm
	queue<int> q;
	for(int i = 0; i < n; i++) {
		if(in_degree[i] == 0) {
			q.push(i);
		}
	}

	while(!q.empty()) {
		int node = q.front();
		q.pop();
		for(int next : edge[node]) {
			in_degree[next]--;
			if(in_degree[next] == 0) q.push(next);
		}

		for(int prev : backedge[node]) {
			dp[node] = (dp[node] + dp[prev]) % 1000000007;
		}
	}
	cout << dp[n] << endl;
	return 0;
}