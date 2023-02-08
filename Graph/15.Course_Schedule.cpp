/*You have to complete n courses. There are m requirements of the form "course a has to be completed before course b". Your task is to find an order in which you can complete the courses.

Input

The first input line has two integers n and m: the number of courses and requirements. The courses are numbered 1,2,…,n.

After this, there are m lines describing the requirements. Each line has two integers a and b: course a has to be completed before course b.

Output

Print an order in which you can complete the courses. You can print any valid order that includes all the courses.

If there are no solutions, print "IMPOSSIBLE".

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
5 3
1 2
3 1
4 5

Output:
3 4 1 5 2
*/

#include <bits/stdc++.h>

using namespace std;


#define pb push_back


int N; // Number of nodes

vector<int> graph[100000], top_sort; // Assume that this graph is a DAG

bool visited[100000];


void dfs(int node) {

	for (int i : graph[node]) {

		if (!visited[i]) {

			visited[i] = true;

			dfs(i);

		}

	}

	top_sort.pb(node);

}


void compute() {

	for (int i = 0; i < N; i++) {

		if (!visited[i]) {

			visited[i] = true;

			dfs(i);

		}

	}

	reverse(begin(top_sort),end(top_sort));

	// The vector `top_sort` is now topologically sorted

}


int main() {

	int M; cin >> N >> M;

	for (int i = 0; i < M; ++i) {

		int a, b; cin >> a >> b;

		graph[a - 1].pb(b - 1);

	}

	compute();

	vector<int> ind(N);

	for (int i = 0; i < N; i++) ind[top_sort[i]] = i;

	for (int i = 0; i < N; i++) for (int j: graph[i]) if (ind[j] <= ind[i]) {

		cout << "IMPOSSIBLE\n"; // topological sort wasn't valid

		exit(0);

	}

	for (int i : top_sort) cout << i + 1 << " ";

	cout << "\n";

}