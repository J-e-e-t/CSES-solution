/*
Your task is to count the number of ways you can fill an n×m grid using 1×2 and 2×1 tiles.

Input

The only input line has two integers n and m.

Output

Print one integer: the number of ways modulo 109+7.

Constraints

    1≤n≤10


1≤m≤1000


Example

Input:
4 7

Output:
781
*/

/*
Time Complexity: $\mathcal O(NM 2^N)$.

We'll process the grid cells column-by-column, row-by-row. Let $i$ and $j$
denote the row and column of the current cell we are considering,
and $\texttt{dp}[i][j][mask]$ be the number of ways to tile the grid so that:

All cells from cell $(0, 0)$ to cell $(i, j - 1)$ are covered.
All cells from cell $(i + 1, j)$ to cell $(N - 1, M - 1)$ are empty.
$mask$ represents whether each of the remaining $N$ cells are empty, with
the $k$-th bit corresponding to the cell in row $k$.


For example, the following state would contribute toward
$\texttt{dp}[1][3][00101_2]$: 
      
    
  
  
    

The answer will be $\texttt{dp}[N - 1][M - 1][0]$.

We now have three cases when calculating $\texttt{dp}[i][j][mask]$:

The $i$-th bit of the mask is 0, meaning that cell $(i, j)$ is covered.

Case 1: we used a horizontal tile to cover it.

Cell $(i, j - 1)$ must have been empty, so there are
$\texttt{dp}[i - 1][j][mask \oplus 2^i]$ ways to do this.


Case 2: we used a vertical tile to cover it.

This is only possible if $i > 0$.
Cell $(i,j-1)$ must have been covered and cell $(i-1,j)$ must have been
empty, so there are $\texttt{dp}[i - 1][j][mask \oplus 2^{i - 1}]$ ways
to do this.
This corresponds to
if (i && !(mask & (1 << i)) && !(mask & (1 << i - 1))) in the code
below.




The $i$-th bit of the mask is 1, meaning that cell $(i, j)$ is empty.

Cell $(i, j - 1)$ must have been covered, so there are
$\texttt{dp}[i - 1][j][mask \oplus 2^i]$ ways to do this.

This is the same as case 1 of when the $i$-th bit of the mask is 0, so we
handle them simultaneously in the code below.






Note that the indices we need to use may become negative and will thus require
wrapping. To simplify calculations and bypass this, simply drop the first two
dimensions of the DP array, as $\texttt{dp}[i][j]$ depends only on
$\texttt{dp}[i - 1][j]$.
*/
// https://usaco.guide/adv/dp-more?lang=cpp

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int dp[1 << 10][2];

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	dp[0][0] = 1;
	for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) {
		for (int mask = 0; mask < (1 << n); mask++) {
			dp[mask][1] = dp[mask ^ (1 << i)][0]; // Horizontal or no tile
			if (i && !(mask & (1 << i)) && !(mask & (1 << i - 1))) // Vertical tile
				dp[mask][1] += dp[mask ^ (1 << i - 1)][0];
			if (dp[mask][1] >= MOD) dp[mask][1] -= MOD;
		}
		for (int mask = 0; mask < (1 << n); mask++) dp[mask][0] = dp[mask][1];
	}
	cout << dp[0][0];
}