/*
Syrjälä's network has n computers and m connections. Your task is to find out if Uolevi can send a message to Maija, and if it is possible, what is the minimum number of computers on such a route.

Input

The first input line has two integers n and m: the number of computers and connections. The computers are numbered 1,2,…,n. Uolevi's computer is 1 and Maija's computer is n.

Then, there are m lines describing the connections. Each line has two integers a and b: there is a connection between those computers.

Every connection is between two different computers, and there is at most one connection between any two computers.

Output

If it is possible to send a message, first print k: the minimum number of computers on a valid route. After this, print an example of such a route. You can print any valid solution.
*/

/*
Time Complexity: $\mathcal{O}(V+E)$

We can observe is that there are many possible shortest paths to output.
Fortunately, the problem states that we can print any valid solution. Notice
that like every other BFS problem, the distance of each node increases by $1$
when we travel to the next level of unvisited nodes. However, the problem
requires that we add additional information - in this case, the path. When we
traverse from node $a$ to $b$, we can set the parent of $b$ to $a$. After the
BFS is complete, this allows us to backtrack through the parents which
ultimately leads us to our starting node. We know to terminate at node $1$
because it's the starting node. If there is no path to our end node, then its
distance will remain at
INT_MAX.

For the test input, we start with the following parent array.

Node
1 2 3 4 5
Parent
0 0 0 0 0
Distance
0 INT_MAX INT_MAX INT_MAX INT_MAX


After visiting children of node $1$:

Node
1 2 3 4 5
Parent
0 1 1 1 0
Distance
0 1 1 1 INT_MAX


After visiting node $5$ from node $4$:

Node
1 2 3 4 5
Parent
0 1 1 1 4
Distance
0 1 1 1 2

To determine the path, we can backtrack from node $n \rightarrow 1$, in this
case $5 \rightarrow 1$, pushing each value that we backtrack into a vector. The
path we take is
$5 \rightarrow \texttt{parent}[5]=4 \rightarrow \texttt{parent}[4] =1$ which
corresponds to the vector $[5, 4, 1]$. We break at node $1$ because it was the
initial starting node. Finally, we reverse the vector and print out its length
(in this case, $3$).

*/
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define pb push_back

int main() {
	int N, M; cin >> N >> M;
	vi dist(N+1,INT_MAX), parent(N+1);
	vector<vi> adj(N+1);
	while (M--) {
		int a,b; cin >> a >> b;
		adj[a].pb(b), adj[b].pb(a);
	}
	queue<int> q;
	dist[1] = 0; q.push(1);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int t: adj[x]) if (dist[t] == INT_MAX) { //dist[t] == INT_MAX is important
			dist[t] = dist[x]+1; parent[t] = x;
			q.push(t);
		}
	}
	if (dist[N] == INT_MAX) cout << "IMPOSSIBLE";
	else {
		cout << dist[N]+1 << "\n";
		vi v{N}; while (v.back() != 1) v.pb(parent[v.back()]);
		reverse(begin(v), end(v));
		for (int t: v) cout << t << " ";
	}
}