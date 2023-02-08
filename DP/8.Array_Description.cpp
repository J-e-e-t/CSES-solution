/*
Array Description

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

You know that an array has n
integers between 1 and m, and the absolute difference between two adjacent values is at most 1.

Given a description of the array where some values may be unknown, your task is to count the number of arrays that match the description.

Input

The first input line has two integers n and m: the array size and the upper bound for each value.

The next line has n integers x1,x2,…,xn: the contents of the array. Value 0 denotes an unknown value.

Output

Print one integer: the number of arrays modulo 109+7.

Constraints

    1≤n≤105


1≤m≤100

0≤xi≤m


Example

Input:
3 5
2 0 2

Output:
3

Explanation: The arrays [2,1,2], [2,2,2] and [2,3,2] match the description. 

*/

/*
dp[i][v] = number of ways to fill the array up to index i, if x[i] = v.

We treat i = 0 separately. Either x[0] = 0, so we can replace it by anything (i.e dp[0][v] = 1 for all v). Otherwise x[0] = v  

0, so that dp[0][v] = 1 is the only allowed value.

Now to the other indices i > 0. If x[i] = 0, we can replace it by any value. However, if we replace it by v, the previous value must be either v-1, v or v+1. Thus the number of ways to fill the array up to i, is the sum of the previous value being v-1, v and v+1. If x[i] = v from the input, only dp[i][v] is allowed (i.e dp[i][j] = 0 if j !=v). Still dp[i][v] = dp[i-1][v-1] + dp[i-1][v] + dp[i-1][v+1].

The complexity is  
with worst-case when x is all zeros.*/

#include <bits/stdc++.h>
using namespace std;

int main() {
  int mod = 1e9+7;
  int n, m;
  cin >> n >> m;
  vector<vector<int>> dp(n,vector<int>(m+1,0));
  int x0;
  cin >> x0;
  if (x0 == 0) {
    fill(dp[0].begin(), dp[0].end(), 1);
  } else {
    dp[0][x0] = 1;
  }
  for (int i = 1; i < n; i++) {
    int x;
    cin >> x;
    if (x == 0) {
      for (int j = 1; j <= m; j++) {
	for (int k : {j-1,j,j+1}) {
	  if (k >= 1 && k <= m) {
	    (dp[i][j] += dp[i-1][k]) %= mod;
	  }
	}
      }
    } else {
      for (int k : {x-1,x,x+1}) {
	if (k >= 1 && k <= m) {
	  (dp[i][x] += dp[i-1][k]) %= mod;
	}
      }
    }
  }
  int ans = 0;
  for (int j = 1; j <= m; j++) {
    (ans += dp[n-1][j]) %= mod;
  }
  cout << ans << endl;
}