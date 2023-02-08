
/*Two Sets II

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

Your task is to count the number of ways numbers 1,2,…,n
can be divided into two sets of equal sum.

For example, if n=7, there are four solutions:

    {1,3,4,6}

and {2,5,7}

{1,2,5,6}
and {3,4,7}

{1,2,4,7}
and {3,5,6}

{1,6,7}
and {2,3,4,5}


Input

The only input line contains an integer n.

Output

Print the answer modulo 109+7.

Constraints

    1≤n≤500


Example

Input:
7

Output:
4
*/

/*
This is a 0-1 knapsack in disguise. If we are to have two subsets of equal sum, they must sum to half the total sum each. This means if the total sum n*(n+1)/2     is odd, the answer is zero (no possibilities). Otherwise we run 0-1 knapsack to get the number of ways to reach
n*(n+1)/4 using subsets of the numbers 1..n-1. Why n-1? Because by only considering numbers up to n-1, we always put n in the second set, and therefore only count each pair of sets once (otherwise we count every pair of sets twice).

dp[i][x] = number of ways to make sum x using subsets of the numbers 1..i .

We say there is one way (the empty set) to make sum 0, so dp[0][0] = 1;

For counting number of ways to make sum x using values up to i, we consider the number i. Either we didn't include it, then there are dp[i-1][x] possibilities, or we included it, and there are dp[i-1][x-i] possibilities. So dp[i][x] = dp[i-1][x] + dp[i-1][x-i].

time  O(N^3)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
  int mod = 1e9+7;
  int n;
  cin >> n;
  int target = n*(n+1)/2;
  if (target%2) {
    cout << 0 << endl;
    return 0;
  }
  target /= 2;

  vector<vector<int>> dp(n,vector<int>(target+1,0));
  dp[0][0] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= target; j++) {
      dp[i][j] = dp[i-1][j];
      int left = j-i;
      if (left >= 0) {
	(dp[i][j] += dp[i-1][left]) %= mod;
      }
    }
  }
  cout << dp[n-1][target] << endl;
}