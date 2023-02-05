/*
You are given an integer n. On each step, you may subtract one of the digits from the number.

How many steps are required to make the number equal to 0?

Input

The only input line has an integer n.

Output

Print one integer: the minimum number of steps.

Constraints

    1≤n≤106


Example

Input:
27

Output:
5

Explanation: An optimal solution is 27→20→18→10→9→0. 
*/
/*

dp[x] = minimum number of operations to go from x to zero.

When considering a number x, for each digit in the decimal representation of x, we can try to remove it. The transition is therefore: dp[x] = min(dp[x-d]) where d belongs to the set of (digits of x)

We initialize dp[0] = 0.

The complexity is O(n)

Note that the greedy solution of always subtracting the maximum digit is also correct, but we are practicing DP :)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> dp(n+1,1e9);
  dp[0] = 0;
  for (int i = 0; i <= n; i++) {
    for (char c : to_string(i)) {
      dp[i] = min(dp[i], dp[i-(c-'0')]+1);
    }
  }
  cout << dp[n] << endl;
}