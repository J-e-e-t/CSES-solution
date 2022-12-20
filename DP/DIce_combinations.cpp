/*
Consider a money system consisting of n coins. Each coin has a positive integer value. Your task is to produce a sum of money x using the available coins in such a way that the number of coins is minimal.

For example, if the coins are {1,5,7} and the desired sum is 11, an optimal solution is 5+5+1 which requires 3 coins.

Input

The first input line has two integers n and x: the number of coins and the desired sum of money.

The second line has n distinct integers c1,c2,…,cn: the value of each coin.

Output

Print one integer: the minimum number of coins. If it is not possible to produce the desired sum, print −1.

Constraints

    1≤n≤100


1≤x≤106

1≤ci≤106


Example

Input:
3 11
1 5 7

Output:
3
*/

#include <bits/stdc++.h>

using namespace std;

long long dp[1000001];

int main() {
	int n;
	cin >> n;
	dp[0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= 6; j++) {
			if(i - j >= 0) {
				dp[i] += dp[i - j];
			}
		}
		dp[i] %= 1000000007;
	}
	cout << dp[n] << "\n";
}