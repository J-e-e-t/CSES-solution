/*Kaaleppi has just robbed a bank and is now heading to the harbor. However, the police wants to stop him by closing some streets of the city.

What is the minimum number of streets that should be closed so that there is no route between the bank and the harbor?

Input

The first input line has two integers n and m: the number of crossings and streets. The crossings are numbered 1,2,…,n. The bank is located at crossing 1, and the harbor is located at crossing n.

After this, there are m lines that describing the streets. Each line has two integers a and b: there is a street between crossings a and b. All streets are two-way streets, and there is at most one street between two crossings.

Output

First print an integer k: the minimum number of streets that should be closed. After this, print k lines describing the streets. You can print any valid solution.

Constraints

    2≤n≤500


1≤m≤1000

1≤a,b≤n


Example

Input:
4 5
1 2
1 3
2 3
3 4
1 4

Output:
2
3 4
1 4
*/
/*
Time Complexity: $\mathcal O(N^2 \cdot M)$

First, we run a max flow algorithm on the graph. Then, we run another BFS from
node $1$. If node $a$ is reachable but node $b$ is not and there was an edge
$a\rightarrow b$, then we know that edge must be removed.
*/

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
using pii = pair<int, int>;
vector<pii> ans;

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
	FOR(i,1,n) FOR(j,1,n) adj[i][j]=oadj[i][j]=0;
	F0R(i,m) {
		ll a,b; cin >> a >> b;
		adj[a][b]++, adj[b][a]++;
		oadj[a][b]++, oadj[b][a]++;
	}
	int v, u;
	while(reachable()) {
		ll flow = 1e18;
		for (v=n; v!=1; v=pa[v]) {
			u = pa[v];
			flow = min(flow, adj[u][v]);
		}
		for (v=n; v!=1; v=pa[v]) {
			u = pa[v];
			adj[u][v] -= flow;
			adj[v][u] += flow;
		}
	}
	reachable();
	FOR(i,1,n) FOR(j,1,n)
	if (V[i] && !V[j] && oadj[i][j]) ans.pb({i,j});
	cout << ans.size() << '\n';
	trav(a, ans) cout << a.f << " " << a.s << '\n';
}