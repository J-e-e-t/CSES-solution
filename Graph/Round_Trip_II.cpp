/*
Byteland has n cities and m flight connections. Your task is to design a round trip that begins in a city, goes through one or more other cities, and finally returns to the starting city. Every intermediate city on the route has to be distinct.

Input

The first input line has two integers n and m: the number of cities and flights. The cities are numbered 1,2,…,n.

Then, there are m lines describing the flights. Each line has two integers a and b: there is a flight connection from city a to city b. All connections are one-way flights from a city to another city.

Output

First print an integer k: the number of cities on the route. Then print k cities in the order they will be visited. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
4 5
1 3
2 1
2 4
3 2
3 4

Output:
4
2 1 3 2*/

/*
Topological sort
We can modify the algorithm above to return a directed cycle in the case where a
topological sort does not exist. To find the cycle, we add each node we visit
onto the stack until we detect a node already on the stack.

For example, suppose that our stack currently consists of $s_1,s_2,\ldots,s_i$
and we then visit $u=s_j$ for some $j\le i$. Then
$s_j\to s_{j+1}\to \cdots\to s_i\to s_j$ is a cycle. We can reconstruct the
cycle without explicitly storing the stack by marking $u$ as not part of the
stack and recursively backtracking until $u$ is reached again.
*/


#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool visited[(int)1e5 + 5], on_stack[(int)1e5 + 5];
vector<int> adj[(int)1e5 + 5];
vector<int> cycle;
int N, M;
bool dfs(int n) {
	visited[n] = on_stack[n] = true;
	for (int u : adj[n]) {
		if(on_stack[u]) {
			cycle.push_back(n); // start cycle
			on_stack[n] = on_stack[u] = false;
			return true;
		}
		else if(!visited[u]) {
			if(dfs(u)) { // continue cycle
				if(on_stack[n]) {
					cycle.push_back(n);
					on_stack[n] = false;
					return true;
				} else { // found u again
					cycle.push_back(n);
					return false;
				}
			}
			if(!cycle.empty()) // finished with cycle
				return false;
		}
	}
	on_stack[n] = false;
	return false;
}
int main()
{
	// take input, etc
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
	}
	for (int i = 1; cycle.empty() && i <= N; i++)
		dfs(i);
	if(cycle.empty())
		cout << "IMPOSSIBLE";
	else {
		reverse(cycle.begin(), cycle.end());
		cout << cycle.size() + 1 << "\n";
		for(int n : cycle) cout << n << " ";
		cout << cycle.at(0);
	}
}