/*
You are going to travel from Syrjälä to Lehmälä by plane. You would like to find answers to the following questions:

    what is the minimum price of such a route?
    how many minimum-price routes are there? (modulo 109+7)


    what is the minimum number of flights in a minimum-price route?
    what is the maximum number of flights in a minimum-price route?

Input

The first input line contains two integers n and m: the number of cities and the number of flights. The cities are numbered 1,2,…,n. City 1 is Syrjälä, and city n is Lehmälä.

After this, there are m lines describing the flights. Each line has three integers a, b, and c: there is a flight from city a to city b with price c. All flights are one-way flights.

You may assume that there is a route from Syrjälä to Lehmälä.

Output

Print four integers according to the problem statement.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n

1≤c≤109


Example

Input:
4 5
1 4 5
1 2 4
2 4 5
1 3 2
3 4 3

Output:
5 2 1 2*/


/*
Explanation

We can run Dijkstra keeping track of

the distance: $\texttt{dist}[]$
the number of ways with the minimum distance: $\texttt{num}[]$
the minimum flights with the minimum distance: $\texttt{minf}[]$, and
the maximum flights with the minimum distance: $\texttt{maxf}[]$.


For every node, $v$, we take into consideration all of its neighbors, $u$. If we
can reach $u$ in a shorter distance than its current minimum, we update the
distance and reset $\texttt{num}[u]$, $\texttt{minf}[u]$, and $\texttt{maxf}[u]$.

We also have to take into
consideration if we can reach $u$ in an equivalent distance. If so, we update:

$$\texttt{num}[u] = \texttt{num}[v] + \texttt{num}[u]$$

$$\texttt{minf}[u] = \min(\texttt{minf}[u], \texttt{minf}[v] + 1)$$

$$\texttt{maxf}[u] = \max(\texttt{maxf}[u], \texttt{maxf}[v] + 1)$$


*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100001;
const ll MAX = 0x3f3f3f3f3f3f3f3f;
const int MOD = int(1e9) + 7;

vector<pair<ll, int>> edge[MAXN];
ll dist[MAXN]; // minimum distance
ll num[MAXN]; // number of ways with the minimum distance
int minf[MAXN]; // minimum flights with minimum distance
int maxf[MAXN]; // maximum flights with minimum distance
bool v[MAXN]; // if a node is visited

void djikstra(int s) {
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

	pq.push({dist[s] = 0, s});
	num[s] = 1;
	while (!pq.empty()) {
		int vert = pq.top().second; pq.pop();

		if (v[vert])
			continue;
		v[vert] = true;
		for (auto [cost, next] : edge[vert]) {
			ll alt = cost + dist[vert];

			if (alt == dist[next]) {
				num[next] = (num[next] + num[vert]) % MOD;
				minf[next] = min(minf[next], minf[vert] + 1);
				maxf[next] = max(maxf[next], maxf[vert] + 1);
			} else if (alt < dist[next]) {
				num[next] = num[vert];
				minf[next] = minf[vert] + 1;
				maxf[next] = maxf[vert] + 1;
				pq.push({dist[next] = alt, next});
			}
		}
	}
}
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0, start, end, cost; i < m; i++) {
		cin >> start >> end >> cost;
		edge[start].push_back({cost, end});
	}
	memset(dist + 1, 0x3f, n * sizeof(long long));
	djikstra(1);
	cout << dist[n] << " " << num[n] << " " << minf[n] << " " << maxf[n];
}