/*
There are n cities and m roads between them. Your task is to process q queries where you have to determine the length of the shortest route between two given cities.

Input

The first input line has three integers n, m and q: the number of cities, roads, and queries.

Then, there are m lines describing the roads. Each line has three integers a, b and c: there is a road between cities a and b whose length is c. All roads are two-way roads.

Finally, there are q lines describing the queries. Each line has two integers a and b: determine the length of the shortest route between cities a and b.

Output

Print the length of the shortest route for each query. If there is no route, print −1 instead.

Constraints

    1≤n≤500


1≤m≤n2

1≤q≤105

1≤a,b≤n

1≤c≤109


Example

Input:
4 3 5
1 2 5
1 3 9
2 3 3
1 2
2 1
1 3
1 4
3 2

Output:
5
5
8
-1
3
*/
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5;

// nodes will be 1-indexed like in the problem
vector<int> adj[MAX_N + 1];

set<int> colors[MAX_N + 1];
int distinct_num[MAX_N + 1];

void process_colors(int curr, int parent) {
	for (int n : adj[curr]) {
		if (n != parent) {
			process_colors(n, curr);
			// make x the larger set always
			if (colors[curr].size() < colors[n].size()) {
				swap(colors[curr], colors[n]);
			}
			for (int item : colors[n]) {
				colors[curr].insert(item);
			}
		}
	}
	distinct_num[curr] = colors[curr].size();
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		colors[i].insert(a);
	}
	for (int i = 1; i < n; i++) {
		int a;
		int b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	process_colors(1, 0);
	for (int i = 1; i <= n; i++) {
		cout << distinct_num[i] << (i < n ? " " : "\n");
	}
}