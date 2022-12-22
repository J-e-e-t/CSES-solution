/*
Your task is to find a minimum-price flight route from Syrjälä to Metsälä. You have one discount coupon, using which you can halve the price of any single flight during the route. However, you can only use the coupon once.

Input

The first input line has two integers n and m: the number of cities and flight connections. The cities are numbered 1,2,…,n. City 1 is Syrjälä, and city n is Metsälä.

After this there are m lines describing the flights. Each line has three integers a, b, and c: a flight begins at city a, ends at city b, and its price is c. Each flight is unidirectional.

You can assume that it is always possible to get from Syrjälä to Metsälä.

Output

Print one integer: the price of the cheapest route from Syrjälä to Metsälä.

When you use the discount coupon for a flight whose price is x, its price becomes ⌊x/2⌋ (it is rounded down to an integer).

Constraints

    2≤n≤105


1≤m≤2⋅105

1≤a,b≤n

1≤c≤109


Example

Input:
3 4
1 2 3
2 3 1
1 3 7
2 1 5

Output:
2
*/

/*
Solution 1

Say we use the discount coupon on the edge between cities A and B.

There are two cases: we can go from $1\rightarrow A\rightarrow B\rightarrow N$,
or $1\rightarrow B\rightarrow A\rightarrow N$. We need to know the distance
between $1$ and $A$, and $N$ and $B$.

We can use Dijkstra's to compute the distance from $1$ and $N$ to every vertex.
Then our answer is
$\min\limits_{A\rightarrow B} \texttt{dist1}[A]+c(A,B)+\texttt{distN}[B]$, where
$c(A,B)$ is the cost to travel from city $A$ to city $B$ after applying the
coupon to that flight, $\texttt{dist1}[A]$ is the cost to travel from city $1$
to city $A$ and $\texttt{distN}[B]$ is the cost to travel from city $B$ to city
$N$.
*/

#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;
using std::pair;

/**
 * given a start point, and an adjacency list with costs,
 * this function gives an array with the minimum distances
 * from all the other nodes to the start node
 * (the value is INT64_MAX if unreachable)
 */
vector<long long> min_costs(
	int from, const vector<vector<pair<int, int>>>& neighbors
) {
	vector<long long> min_costs(neighbors.size(), INT64_MAX);
	min_costs[from] = 0;
	std::priority_queue<pair<long long, int>> frontier;
	frontier.push({0, from});
	while (!frontier.empty()) {
		pair<long long, int> curr_state = frontier.top();
		frontier.pop();
		int curr = curr_state.second;
		if (-curr_state.first != min_costs[curr]) {
			continue;
		}
		
		for (auto [n, nc] : neighbors[curr]) {
			long long new_cost = min_costs[curr] + nc;
			if (new_cost < min_costs[n]) {
				min_costs[n] = new_cost;
				frontier.push({-new_cost, n});
			}
		}
	}
	return min_costs;
}

int main() {
	int city_num;
	int flight_num;
	std::cin >> city_num >> flight_num;
	vector<vector<pair<int, int>>> neighbors(city_num);
	vector<vector<pair<int, int>>> reverse_neighbors(city_num);
	for (int f = 0; f < flight_num; f++) {
		int from;
		int to;
		int cost;
		std::cin >> from >> to >> cost;
		neighbors[--from].push_back({--to, cost});
		reverse_neighbors[to].push_back({from, cost});
	}
 
	vector<long long> start_costs = min_costs(0, neighbors);
	vector<long long> end_costs = min_costs(city_num - 1, reverse_neighbors);
	long long total_min = INT64_MAX;
	for (int c = 0; c < city_num; c++) {
		for (auto [n, nc] : neighbors[c]) {
			if (start_costs[c] == INT64_MAX || end_costs[n] == INT64_MAX) {
				continue;
			}
			total_min = std::min(
				total_min,
				start_costs[c] + (nc / 2) + end_costs[n]
			);
		}
	}
	cout << total_min << endl;
}

/*
Solution 2

Alternatively, we can run Dijkstra's and modify our distance array slightly to
track whether the discount has been used or not.

$\texttt{dist}[i][\texttt{false}]$ will represent the shortest distance from the start node
to node $i$, without using the discount. $\texttt{dist}[i][\texttt{true}]$ will represent
the shortest distance after using the discount.
*/

// #include <iostream>
// #include <vector>
// #include <queue>

// using std::cout;
// using std::endl;
// using std::vector;

// int main() {
// 	int city_num;
// 	int flight_num;
// 	std::cin >> city_num >> flight_num;
// 	vector<vector<std::pair<int, int>>> neighbors(city_num);
// 	for (int f = 0; f < flight_num; f++) {
// 		int from;
// 		int to;
// 		int cost;
// 		std::cin >> from >> to >> cost;
// 		neighbors[--from].push_back({--to, cost});
// 	}
 
// 	vector<vector<long long>> min_cost(city_num, {INT64_MAX, INT64_MAX});
// 	min_cost[0] = {0, 0};
 
// 	struct Pos {
// 		int pos;  // the current position
// 		bool used;  // whether we've used up our discount yet
// 		long long cost;  // the cost associated with this state
// 	};
// 	auto cmp = [&] (const Pos& a, const Pos& b) { return a.cost > b.cost; };
// 	std::priority_queue<Pos, vector<Pos>, decltype(cmp)> frontier(cmp);
// 	frontier.push({0, false, 0});
	
// 	while (!frontier.empty()) {
// 		Pos curr = frontier.top();
// 		frontier.pop();
// 		long long curr_cost = min_cost[curr.pos][curr.used];
// 		if (curr_cost != curr.cost) {
// 			continue;
// 		}
// 		if (curr.pos == city_num - 1) {
// 			break;
// 		}
// 		for (auto [n, nc] : neighbors[curr.pos]) {
// 			// if we haven't used the discount yet, try using it now
// 			if (!curr.used) {
// 				long long new_cost = curr_cost + nc / 2;
// 				if (new_cost < min_cost[n][true]) {
// 					min_cost[n][true] = new_cost;
// 					frontier.push(Pos{n, true, new_cost});
// 				}
// 			}
// 			// but we can always just try the normal cost route
// 			if (curr_cost + nc < min_cost[n][curr.used]) {
// 				min_cost[n][curr.used] = curr_cost + nc;
// 				frontier.push(Pos{n, curr.used, curr_cost + nc});
// 			}
// 		}
// 	}
// 	cout << min_cost[city_num - 1][1];
// }