/*
You have n coins with certain values. Your task is to find all money sums you can create using these coins.

Input

The first input line has an integer n: the number of coins.

The next line has n integers x1,x2,…,xn: the values of the coins.

Output

First print an integer k: the number of distinct money sums. After this, print all possible sums in increasing order.

Constraints

    1≤n≤100


1≤xi≤1000


Example

Input:
4
4 2 5 2

Output:
9
2 4 5 6 7 8 9 11 13
*/

/*
Solution

Time Complexity: $\mathcal{O}(N\cdot X)$

For this problem, we'll define $\texttt{dp[i][j]}$ as if it is possible to make
a sum of $j$ with $i$ coins.

And if we loop through all the coins and possible sums, then we'll get two
possible situations:

If it is possible to make a sum of $j$ with less than $i$
coins, then make the same sum with more than $i$ coins will also be possible.

And if it is possible to make a sum of $\texttt{current\_sum - coin\_value[i]}$
with $i - 1$ coins, then make a sum of $\texttt{current\_sum}$ with
$i$ coins will also be possible.

And at the end, we can loop through the $\texttt{dp}$ array, find all the
possible $\texttt{sums}$ with $n$ coins, put them in a dynamic
array, then print out the size of that dynamic array and every elements in it.
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100;
const int MAX_SUM = 1e5;

bool dp[MAX_N + 1][MAX_SUM + 1];

int main() {
	int n;
	cin >> n;

	vector<int> coins_values(n);
	for (int i = 0; i < n; i++) {
		cin >> coins_values[i];
	}

	dp[0][0] = true;

	for (int i = 1; i <= n; i++) {
		for (int current_sum = 0; current_sum <= MAX_SUM; current_sum++) {
			dp[i][current_sum] = dp[i - 1][current_sum];
			int prev_sum = current_sum - coins_values[i - 1];
			if (prev_sum >= 0 && dp[i - 1][prev_sum]) {
				dp[i][current_sum] = true;
			}
		}
	}

	vector<int> possible;
	for (int sum = 1; sum <= MAX_SUM; sum++) {
		if (dp[n][sum]) {
			possible.push_back(sum);
		}
	}

	cout << (int)(possible.size()) << endl;

	for (int sum : possible) {
		cout << sum << " ";
	}
	cout << endl;
}