/*
There are n cities and m flight connections between them. Your task is to determine the length of the shortest route from Syrjälä to every city.

Input

The first input line has two integers n and m: the number of cities and flight connections. The cities are numbered 1,2,…,n, and city 1 is Syrjälä.

After that, there are m lines describing the flight connections. Each line has three integers a, b and c: a flight begins at city a, ends at city b, and its length is c. Each flight is a one-way flight.

You can assume that it is possible to travel from Syrjälä to all other cities.

Output

Print n integers: the shortest route lengths from Syrjälä to cities 1,2,…,n.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n

1≤c≤109


Example

Input:
3 4
1 2 6
1 3 2
3 2 3
1 3 4

Output:
0 5 2
*/

/*
Implementation from CPH book

for (int i = 1; i <= n; i++) distance[i] = INF;
distance[x] = 0;
q.push({0,x});
while (!q.empty()) {
    int a = q.top().second; q.pop();
    if (processed[a]) continue;
    processed[a] = true;
    for (auto u : adj[a]) {
        int b = u.first, w = u.second;

        if (distance[a]+w < distance[b]) {
            distance[b] = distance[a]+w;
            q.push({-distance[b],b});
        }
    }
}
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back

vector<pair<int, int>> graph[100000];
// Adjacency list of (neighbour, edge weight)
ll dist[100000];
int N;

void dijkstra(int src) { // Source and destination
	for (int i = 0; i < N; ++i) dist[i] = LLONG_MAX;
	// Set all distances to infinity

	using T = pair<ll,int>; priority_queue<T,vector<T>,greater<T>> pq;
	dist[src] = 0; // The shortest path from a node to itself is 0
	pq.push({0, src});

	while (pq.size()) {
		ll cdist; int node; tie(cdist, node) = pq.top(); pq.pop();
		if (cdist != dist[node]) continue;
		for (pair<int, int> i : graph[node]) {
			// If we can reach a neighbouring node faster,
			// we update its minimum distance
			if (cdist+i.second < dist[i.first]) {
				pq.push({dist[i.first] = cdist+i.second, i.first});
			}
		}
	}
}

int main() {
	int M; cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a,b,c; cin >> a >> b >> c;
		graph[a-1].pb({b-1,c});
	}
	dijkstra(0);
	for (int i = 0; i < N; ++i) cout << dist[i] << " ";
}