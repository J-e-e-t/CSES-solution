/*
There is a list of n numbers and two players who move alternately. On each move, a player removes either the first or last number from the list, and their score increases by that number. Both players try to maximize their scores.

What is the maximum possible score for the first player when both players play optimally?

Input

The first input line contains an integer n: the size of the list.

The next line has n integers x1,x2,…,xn: the contents of the list.

Output

Print the maximum possible score for the first player.

Constraints

    1≤n≤5000


−109≤xi≤109


Example

Input:
4
4 5 1 3

Output:
8
*/

/*
The trick here is to see that since the sum of the two players' scores is the sum of the input list, player 1 tries to maximize score1-score2 , while player 2 tries to minimize it.
dp[l][r] = difference score1- score2  if considering the game played only on interval [l, r].

If the interval contains only one element (l = r), then the first player must take that element. So dp[i][i] = x[i].

Otherwise, player 1 can choose to take the first element or the last element. If he takes the first element, he gets x[l] points, and we are left with the interval [l+1,r], but with player 2 starting.score1 - score2      
on interval [l+1,r] is just dp[l+1][r] if player 1 starts. Since player 2 starts, it is -dp[l+1][r]. Thus, the difference of scores will be x[l]-dp[l+1][r] if player 1 chooses the first element. Similarly, it will be x[r]-dp[l][r-1] if he chooses the last element. He always chooses the maximum of those,
 so dp[l][r] = max(x[l]-dp[l+1][r], x[r]-dp[l][r-1]).

 In this problem dp[l][r] depends on dp[l+1][r], and therefore we need to compute larger l before smaller l. We do it by looping through l from high to low. r still needs to go from low to high, since we depend only on smaller r (dp[l][r] depends on dp[l][r-1]). Note that in all the other problems in this editorial, dp only depends on smaller indices (like dp[x] depending on dp[x-v], or dp[i][x] depending on dp[i-1][x]), which means looping through indices in increasing order is correct.

We can reconstruct the score of player 1 as the mean of, the sum of all input values, and score1 - score2

Time - O(N^2)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> x(n);
  long long sum = 0;
  for (int&v : x) {
    cin >> v;
    sum += v;
  }

  vector<vector<long long>> dp(n,vector<long long>(n));
  for (int l = n-1; l >= 0; l--) {
    for (int r = l; r < n; r++) {
      if (l == r) {
	dp[l][r] = x[l];
      } else {
	dp[l][r] = max(x[l]-dp[l+1][r],
		       x[r]-dp[l][r-1]);
      }
    }
  }
  cout << (sum+dp[0][n-1])/2 << endl;
}