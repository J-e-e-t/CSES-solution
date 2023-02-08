/*Consider a network consisting of n computers and m connections. Each connection specifies how fast a computer can send data to another computer.

Kotivalo wants to download some data from a server. What is the maximum speed he can do this, using the connections in the network?

Input

The first input line has two integers n and m: the number of computers and connections. The computers are numbered 1,2,…,n. Computer 1 is the server and computer n is Kotivalo's computer.

After this, there are m lines describing the connections. Each line has three integers a, b and c: computer a can send data to computer b at speed c.

Output

Print one integer: the maximum speed Kotivalo can download data.

Constraints

    1≤n≤500


1≤m≤1000

1≤a,b≤n

1≤c≤109


Example

Input:
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3

Output:
6
*/
// Time Complexity: $\mathcal O(N^2 \cdot M)$

// Just find the max flow of the graph using your favourite max flow algorithm.

// The code below uses Dinic's maxflow algorithm.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)

#define F0R(i,a) for(int i=0; i<(a); i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)
#define R0F(i,a) for(int i=(a)-1; i>=0; i--)
#define ROF(i,a,b) for(int i=(b); i>=a; i--)
#define trav(a,x) for (auto& a: x)

int n, m;
ll adj[501][501], oadj[501][501];

ll flow[501];
bool V[501];
int pa[501];

bool reachable() {
	memset(V, false, sizeof(V));
	queue<int> Q; Q.push(1); V[1]=1;
	while(!Q.empty()) {
		int i=Q.front(); Q.pop();
		FOR(j,1,n) if (adj[i][j] && !V[j])
			V[j]=1, pa[j]=i, Q.push(j);
	}
	return V[n];
}

int main() {
	cin >> n >> m;
	FOR(i,1,n) FOR(j,1,n) adj[i][j] = 0;
	F0R(i,m) {
		ll a,b,c; cin >> a >> b >> c;
		adj[a][b] += c;
	}
	int v, u;
	ll maxflow = 0;
	while(reachable()) {
		ll flow = 1e18;
		for (v=n; v!=1; v=pa[v]) {
			u = pa[v];
			flow = min(flow, adj[u][v]);
		}
		maxflow += flow;
		for (v=n; v!=1; v=pa[v]) {
			u = pa[v];
			adj[u][v] -= flow;
			adj[v][u] += flow;
		}
	}
	cout << maxflow << '\n';
}