/*
A game has n levels and m teleportes between them. You win the game if you move from level 1 to level n using every teleporter exactly once.

Can you win the game, and what is a possible way to do it?

Input

The first input line has two integers n and m: the number of levels and teleporters. The levels are numbered 1,2,…,n.

Then, there are m lines describing the teleporters. Each line has two integers a and b: there is a teleporter from level a to level b.

You can assume that each pair (a,b) in the input is distinct.

Output

Print m+1 integers: the sequence in which you visit the levels during the game. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

Constraints

    2≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
5 6
1 2
1 3
2 4
2 5
3 1
4 2

Output:
1 3 1 2 4 2 5

*/
#include <bits/stdc++.h>


using namespace std;


const int MAX_N = 1e5 + 5;


int n, m, in_deg[MAX_N], out_deg[MAX_N];

vector<int> adj[MAX_N];


// print the euler path (from 1 to n) in a directed graph

void euler() { 

	if (out_deg[1] != in_deg[1] + 1 || in_deg[n] != out_deg[n] + 1) {

		cout << "IMPOSSIBLE\n";

		return;

	}

	for (int i = 2; i < n; i++) {

		if (in_deg[i] != out_deg[i]) {

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

			int v = adj[u].back(); adj[u].pop_back();

			st.push(v);

		}

	}

	if ((int) res.size() != m + 1) {

		cout << "IMPOSSIBLE\n";

		return;

	}

	reverse(res.begin(), res.end());

	for (int u : res) cout << u << " ";

	cout << "\n";

}


int main() {

	ios_base::sync_with_stdio(0);

	cin.tie(0); cout.tie(0);

	

	cin >> n >> m;

	for (int i = 0; i < m; i++) {

		int u, v; cin >> u >> v;

		adj[u].push_back(v);

		out_deg[u]++; in_deg[v]++;

	}

	euler();

}