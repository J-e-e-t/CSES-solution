/*
There are n cities and m flight connections between them. You want to travel from Syrjälä to Lehmälä so that you visit each city exactly once. How many possible routes are there?

Input

The first input line has two integers n and m: the number of cities and flights. The cities are numbered 1,2,…,n. City 1 is Syrjälä, and city n is Lehmälä.

Then, there are m lines describing the flights. Each line has two integers a and b: there is a flight from city a to city b. All flights are one-way flights.

Output

Print one integer: the number of routes modulo 109+7.

Constraints

    2≤n≤20


1≤m≤n2

1≤a,b≤n


Example

Input:
4 6
1 2
1 3
2 3
3 2
2 4
3 4

Output:

*/
/*
Let $dp[S][i]$ be the number of routes that visit all the cities in the subset
$S$ and end at city $i$. The transitions will then be:
$$dp[S][i] = \sum_{x \in adj[i]} dp[S \setminus \{i\}][x] \text{ if $x \in S$}$$
where $S \setminus \{i\}$ is the subset $S$ without city $i$.
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_N = 20;
const ll MOD = (ll) 1e9 + 7;

ll dp[1 << MAX_N][MAX_N];
// come_from[i] contains the cities that can fly to i
vector<int> come_from[MAX_N];

int main() {
	int city_num;
	int flight_num;
	cin >> city_num >> flight_num;
	for (int f = 0; f < flight_num; f++) {
		int start, end;
		cin >> start >> end;
		come_from[--end].push_back(--start);
	}
	
	dp[1][0] = 1;
	for (int s = 2; s < 1 << city_num; s++) {
		// only consider subsets that have the first city
		if ((s & (1 << 0)) == 0)
			continue;
		// also only consider subsets with the last city if it's the full subset
		if ((s & (1 << (city_num - 1))) && s != ((1 << city_num) - 1))
			continue;

		for (int end = 0; end < city_num; end++) {
			if ((s & (1 << end)) == 0)
				continue;
			
			// the subset that doesn't include the current end
			int prev = s - (1 << end);
			for (int j : come_from[end]) {
				if ((s & (1 << j))) {
					dp[s][end] += dp[prev][j];
					dp[s][end] %= MOD;
				}
			}	
		}
	}
	cout << dp[(1 << city_num) - 1][city_num - 1] << '\n';
}