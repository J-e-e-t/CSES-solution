
/*
Consider an n×n grid whose squares may have traps. It is not allowed to move to a square with a trap.

Your task is to calculate the number of paths from the upper-left square to the lower-right square. You can only move right or down.

Input

The first input line has an integer n: the size of the grid.

After this, there are n lines that describe the grid. Each line has n characters: . denotes an empty cell, and * denotes a trap.

Output

Print the number of paths modulo 109+7.

Constraints

    1≤n≤1000


Example

Input:
4
....
.*..
...*
*...

Output:
3
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool ok[1000][1000];
ll dp[1000][1000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for(int j = 0; j < n; j++) {
			if(s[j] == '.') ok[i][j] = true;
			else ok[i][j] = false;
		}
	}

	dp[0][0] = 1;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(!ok[i][j]) dp[i][j] = 0;
			else {
				if(i > 0) dp[i][j] += dp[i - 1][j];
				if(j > 0) dp[i][j] += dp[i][j - 1];
				dp[i][j] %= 1000000007;
			}
		}
	}

	cout << dp[n - 1][n - 1] << "\n";

	return 0;
}