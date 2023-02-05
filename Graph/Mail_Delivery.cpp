/*
Your task is to deliver mail to the inhabitants of a city. For this reason, you want to find a route whose starting and ending point are the post office, and that goes through every street exactly once.

Input

The first input line has two integers n and m: the number of crossings and streets. The crossings are numbered 1,2,…,n, and the post office is located at crossing 1.

After that, there are m lines describing the streets. Each line has two integers a and b: there is a street between crossings a and b. All streets are two-way streets.

Every street is between two different crossings, and there is at most one street between two crossings.

Output

Print all the crossings on the route in the order you will visit them. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

Constraints

2≤n≤105
1≤m≤2.105
1≤a,b≤n

Example

Input:
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5

Output:
1 2 6 3 2 4 5 3 1
*/

#include <bits/stdc++.h>


using namespace std;


const int MAX_N = 1e5 + 5;


int n, m;

set<int> adj[MAX_N];


// print the euler circuit in an undirected graph

void euler() { 

	for (int i = 1; i <= n; i++) {

		if (adj[i].size() % 2) {

			cout << "IMPOSSIBLE\n";

			return;

		}

	}

	vector<int> res;

	stack<int> st; st.push(1);

	while (st.size()) {

		int u = st.top();

		if (adj[u].empty()) {

			res.push_back(u);

			st.pop();

		} else {

			int v = *adj[u].begin();

			adj[u].erase(v);

			adj[v].erase(u);

			st.push(v);

		}

	}

	if ((int) res.size() != m + 1) {

		cout << "IMPOSSIBLE\n";

		return;

	}

	for (int u : res) cout << u << " ";

	cout << "\n";

}


int main() {

	ios_base::sync_with_stdio(0);

	cin.tie(0); cout.tie(0);


	cin >> n >> m;

	for (int i = 0; i < m; i++) {

		int u, v; cin >> u >> v;

		adj[u].insert(v);

		adj[v].insert(u);

	}

	euler();

}