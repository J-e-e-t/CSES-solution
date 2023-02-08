/*
There are n houses on a street, numbered 1,2,…,n. The distance of houses a and b is |a−b|. You know the number of children in each house.

Your task is to establish k schools in such a way that each school is in some house. Then, each child goes to the nearest school. What is the minimum total walking distance of the children if you act optimally?

Input

The first input line has two integers n and k: the number of houses and the number of schools. The houses are numbered 1,2…,n.

After this, there are n integers c1,c2,…,cn: the number of children in each house.

Output

Print the minimum total distance.

Constraints

    1≤k≤n≤3000


1≤ci≤109


Example

Input:
6 2
2 7 1 4 6 4

Output:
11

Explanation: Houses 2 and 5 will have schools. */

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 3005;
int a[mxN], pre[3][mxN];
int dp[mxN][mxN]; //dp[i][j] = min cost for j divisions with 1 school at i.
const int INF = 1LL<<60;
int n;

int cost(int a, int b) {
    int m = (a+b)/2;
    int ans = (pre[1][m] - pre[1][a-1]) - a*(pre[0][m] - pre[0][a-1]);
    ans += (pre[2][b] - pre[2][m]) - (n-b+1)*(pre[0][b] - pre[0][m]);
    return ans;
}

void solve(int j, int a, int b, int x, int y) {
    if (a > b)
        return;
    int m = (a + b) / 2;
    pair<int, int> p = {INF, -1};
    for (int i = x; i <= min(m, y); i++) {
        p = min(p, {dp[i][j-1] + cost(i, m), i});
    }
    dp[m][j] = p.first;
    solve(j, a, m-1, x, p.second);
    solve(j, m+1, b, p.second, y);    
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[0][i+1] = pre[0][i] + a[i];
        pre[1][i+1] = pre[1][i] + (i+1)*a[i];
        pre[2][i+1] = pre[2][i] + (n-i)*a[i];
    }

    for (int i = 1; i <= n; i++) 
        dp[i][1] = (pre[2][i] - pre[2][0]) - (n-i+1)*(pre[0][i] - pre[0][0]);

    for (int i = 2; i <= k; i++) {
        solve(i, 1, n, 1, n);
    }
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[i][k] + (pre[1][n] - pre[1][i-1]) - i*(pre[0][n] - pre[0][i-1]));
    }
    cout << ans;
}
