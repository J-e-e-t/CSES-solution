/*
There are n people who want to get to the top of a building which has only one elevator. You know the weight of each person and the maximum allowed weight in the elevator. What is the minimum number of elevator rides?

Input

The first input line has two integers n and x: the number of people and the maximum allowed weight in the elevator.

The second line has n integers w1,w2,…,wn: the weight of each person.

Output

Print one integer: the minimum number of rides.

Constraints

    1≤n≤20


1≤x≤109

1≤wi≤x


Example

Input:
4 10
4 8 6 1

Output:
2
*/



// Time Complexity:
 
// $\mathcal{O}(N\cdot 2^N)$

//BeginCodeSnip{C++ Short Template}
#include <bits/stdc++.h> // see /general/running-code-locally
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

void setIO(string name = "") {
	cin.tie(0)->sync_with_stdio(0); // see /general/fast-io
	if (sz(name)) {
		freopen((name + ".in").c_str(), "r", stdin); // see /general/input-output
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
//EndCodeSnip

int main() {
	int people, maxWeight;
	cin >> people >> maxWeight;
	vector<int> weight(people);
	for (int& i : weight)
		cin >> i;

	vector<pair<int, int>> dp(1 << people, { people + 1, maxWeight + 1 });
	dp[0] = make_pair(1, 0);
	/* 
	 * Loop through all bitmasks.
	 * The bitmasks represent whether each person has used the elevator or not.
	 * If the ith bit is set, this means the ith person has used the elevator.
	 */
	for (int mask = 1; mask < (1 << people); mask++) {
		for (int i = 0; i < people; i++)
			// The ith person has used the elevator.
			if (mask & (1 << i)) {
				auto prev = dp[mask ^ (1 << i)];
				int numRides = prev.first;
				int totalWeight = prev.second;
				// We need to use a new ride.
				if (totalWeight + weight[i] <= maxWeight)
					totalWeight += weight[i];
				else {
					// Add the weight of the ith person to the current ride.
					numRides++;
					totalWeight = weight[i];
				}
				// Update if it is better than the original.
				dp[mask] = min(dp[mask], make_pair(numRides, totalWeight));
			}
	}
	// Result when all people have used the elevator.
	cout << dp[(1 << people) - 1].first;
}