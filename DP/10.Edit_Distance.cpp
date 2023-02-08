/*
The edit distance between two strings is the minimum number of operations required to transform one string into the other.

The allowed operations are:

    Add one character to the string.
    Remove one character from the string.
    Replace one character in the string.

For example, the edit distance between LOVE and MOVIE is 2, because you can first replace L with M, and then add I.

Your task is to calculate the edit distance between two strings.

Input

The first input line has a string that contains n characters between A–Z.

The second input line has a string that contains m characters between A–Z.

Output

Print one integer: the edit distance between the strings.

Constraints

    1≤n,m≤5000


Example

Input:
LOVE
MOVIE

Output:
2
*/

/*
This is a classic problem called edit distance.

We call the input strings a and b, and refer to the first i characters of a by a[:i].

dp[i][k] = minimum number of moves to change a[:i] to b[:k].

When we calculate dp[i][k], there are four possibilities to consider for the rightmost operation. We check all of them and take the cheapest one.

1. We deleted character a[i-1]. This took one operation, and we still need to change a[:i-1] to b[:k]. So this costs 1 + dp[i-1][k] operations.

2. We added character b[k-1] to the end of a[:i]. This took one operation, and we still need to change a[:i] to b[:k-1]. So this costs 1 + dp[i][k-1] operations.

3. We replaced a[i-1] with b[k-1]. This took one operation, and we still need to change a[:i-1] to b[:k-1]. So this costs 1 + dp[i-1][k-1] operations.

4. a[i-1] was already equal to b[k-1], so we just need to change a[:i-1] to b[:k-1]. That takes dp[i-1][k-1] operations. This possibility can be viewed as a replace operation where we don't actually need to replace a[i-1].

Time Complexity O(|a| * |b|)*/

#include <bits/stdc++.h>
using namespace std;

int main() {
  string a, b;
  cin >> a >> b;
  int na = a.size(), nb = b.size();
  vector<vector<int>> dp(na+1, vector<int>(nb+1,1e9));
  dp[0][0] = 0;
  for (int i = 0; i <= na; i++) {
    for (int j = 0; j <= nb; j++) {
      if (i) {
	dp[i][j] = min(dp[i][j], dp[i-1][j]+1);
      }
      if (j) {
	dp[i][j] = min(dp[i][j], dp[i][j-1]+1);
      }
      if (i && j) {
	dp[i][j] = min(dp[i][j], dp[i-1][j-1]+(a[i-1] != b[j-1]));
      }
    }
  }
  cout << dp[na][nb] << endl;
}