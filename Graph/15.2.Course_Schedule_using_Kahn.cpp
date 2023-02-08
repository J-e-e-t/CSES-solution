/*
Pro Tip

If the length of the array containing the end order does not equal the number of elements that need to be sorted, then there is a cycle in the graph.

Optional

We can also use Kahn's algorithm to extract the lexicographically minimum topological sort by breaking ties lexographically.

Although the above code does not do this, one can simply replace the queue with a priority_queue to implement this extension.
*/
#include <iostream>

#include <vector>

#include <queue>

using namespace std;


const int MAX_N = 100000;


int main()

{

	int n, m;

	cin >> n >> m;

	vector<int> graph[MAX_N];

	int indegree[MAX_N]{};

	queue<int> q;

	for (int i = 0; i < m; i++)

	{

		int a, b;

		cin >> a >> b;

		graph[a - 1].push_back(b - 1);

		indegree[b - 1]++;

	}

	for (int i = 0; i < n; i++)

	{

		// locate the nodes with indegree 0 and push them into the queue

		if (indegree[i] == 0)

		{

			q.push(i);

		}

	}

	vector<int> order;

	while (!q.empty())

	{

		int curr = q.front();

		q.pop();

		// add the current node to the order

		order.push_back(curr);

		for (int next : graph[curr])

		{

			// remove the current node from the graph

			indegree[next]--;

			// push any new nodes with indegree 0 into the queue

			if (indegree[next] == 0)

			{

				q.push(next);

			}

		}

	}

	// if there isn't a valid topological sorting

	if (order.size() != n)

	{

		cout << "IMPOSSIBLE" << endl;

		return 0;

	}

	cout << order[0] + 1;

	for (int i = 1; i < n; i++)

	{

		cout << " " << order[i] + 1;

	}

	cout << endl;

	return 0;

}