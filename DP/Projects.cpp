
/*
There are n projects you can attend. For each project, you know its starting and ending days and the amount of money you would get as reward. You can only attend one project during a day.

What is the maximum amount of money you can earn?

Input

The first input line contains an integer n: the number of projects.

After this, there are n lines. Each such line has three integers ai, bi, and pi: the starting day, the ending day, and the reward.

Output

Print one integer: the maximum amount of money you can earn.

Constraints

    1≤n≤2⋅105


1≤ai≤bi≤109

1≤pi≤109


Example

Input:
4
2 4 4
3 6 6
6 8 2
5 7 3

Output:
7
*/


/*
Even though days can go up to 10^9  , we only care about days where we either start or just finished a project. So before doing anything else, we compress all days to their index among all interesting days (i.e days corresponding to ai or bi +1   for some i). This way, days range from 0 to less than
2n <= 4*10^5
dp[i] = maximum amount of money we can earn before day i.

On day i, maybe we just did nothing, so we earn what we earned on day i-1, i.e dp[i-1]. Otherwise, we just finished some project. We earned some money doing the project, and use dp[start of project] to know how much money we could have earned before starting the project. Loop through all projects finishing just before day i, and take the best one.

The complexity is O(N*Log N) ,log comes from day compression
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  map<int,int> compress;
  vector<int> a(n),b(n),p(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i] >> p[i];
    b[i]++;
    compress[a[i]], compress[b[i]];
  }

  int coords = 0;
  for (auto&v : compress) {
    v.second = coords++;
  }

  vector<vector<pair<int,int>>> project(coords);
  for (int i = 0; i < n; i++) {
    project[ compress[b[i]] ].emplace_back( compress[a[i]], p[i] );
  }

  vector<long long> dp(coords, 0);
  for (int i = 0; i < coords; i++) {
    if (i > 0) {
      dp[i] = dp[i-1];
    }
    for (auto p : project[i]) {
      dp[i] = max(dp[i], dp[p.first]+p.second);
    }
  }
  cout << dp[coords-1] << endl;
}