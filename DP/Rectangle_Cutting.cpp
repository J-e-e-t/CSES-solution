/*
Given an a×b rectangle, your task is to cut it into squares. On each move you can select a rectangle and cut it into two rectangles in such a way that all side lengths remain integers. What is the minimum possible number of moves?

Input

The only input line has two integers a and b.

Output

Print one integer: the minimum number of moves.

Constraints

    1≤a,b≤500


Example

Input:
3 5

Output:
3
*/

/*
dp[w][h] = minimum number of cuts needed to cut a w x h piece into squares.

Consider a  w * h piece. If it is already square (w = h), we need 0 cuts. Otherwise, we need to make the first cut either horizontally or vertically. Say we make it horizontally, then we can cut at any position 1,2,..,h-1. If we cut at position k, then we are left with two pieces of sizes w * k and w* (h-k)  .
 We can look up the number of moves to reduce these to squares in the dp array. We loop over all possibilities k and take the best one. Similarly for vertical cuts.
 
 Time -  O( a^2*b + a*b^2)*/

 #include <bits/stdc++.h>
using namespace std;

int main() {
  int w, h;
  cin >> w >> h;
  vector<vector<int>> dp(w+1,vector<int>(h+1));
  for (int i = 0; i <= w; i++) {
    for (int j = 0; j <= h; j++) {
      if (i == j) {
	dp[i][j] = 0;
      } else {
	dp[i][j] = 1e9;
	for (int k = 1; k < i; k++) {
	  dp[i][j] = min(dp[i][j], dp[k][j]+dp[i-k][j]+1);
	}
	for (int k = 1; k < j; k++) {
	  dp[i][j] = min(dp[i][j], dp[i][k]+dp[i][j-k]+1);
	}
      }
    }
  }
  cout << dp[w][h] << endl;
}