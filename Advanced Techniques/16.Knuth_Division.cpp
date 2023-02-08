/*
Given an array of n numbers, your task is to divide it into n subarrays, each of which has a single element.

On each move, you may choose any subarray and split it into two subarrays. The cost of such a move is the sum of values in the chosen subarray.

What is the minimum total cost if you act optimally?

Input

The first input line has an integer n: the array size. The array elements are numbered 1,2,…,n.

The second line has n integers x1,x2,…,xn: the contents of the array.

Output

Print one integer: the minimum total cost.

Constraints

    1≤n≤5000


1≤xi≤109


Example

Input:
5
2 7 3 2 5

Output:
43
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 5e3+5;
pair<int, int> dp[mxN][mxN];
int pre[mxN];
const int INF = 1LL<<60;

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n; cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        pre[i] = pre[i-1] + x;
    }
    for (int i = 1; i < n; i++) {
        dp[i][i+1] = {pre[i+1] - pre[i-1], i};
    }

    for (int k = 3; k <= n; k++) {
        for (int i = 1; i+k-1 <= n; i++) {
            int j = i+k-1;
            pair<int, int> p = {dp[i][j-1].second, dp[i+1][j].second};
            dp[i][j] = {INF, -1};
            for (int x = p.first; x <= p.second; x++) {
                dp[i][j] = min(dp[i][j], {dp[i][x].first + dp[x+1][j].first, x});
            }
            dp[i][j].first += pre[j] - pre[i-1];
        }
    }
    cout << dp[1][n].first;
    
}