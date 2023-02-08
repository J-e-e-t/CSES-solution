/*
A directed acyclic graph consists of n nodes and m edges. The nodes are numbered 1,2,…,n.

Calculate for each node the number of nodes you can reach from that node (including the node itself).

Input

The first input line has two integers n and m: the number of nodes and edges.

Then there are m lines describing the edges. Each line has two distinct integers a and b: there is an edge from node a to node b.

Output

Print n integers: for each node the number of reachable nodes.

Constraints

    1≤n≤5⋅104


1≤m≤105


Example

Input:
5 6
1 2
1 3
1 4
2 3
3 5
4 5

Output:
5 3 2 2 1
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 5e4 + 5;
vector<bitset<mxN>> dp(mxN);
vector<int> v, adj[mxN];
bool vis[mxN];

void dfs(int s) {
    if (vis[s]) return;
    vis[s] = 1;
    for (auto i: adj[s])
        dfs(i);
    v.push_back(s);
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
    }
    for (int i = 1; i <= n; i++)
        dfs(i);

    for (auto s: v) {
        dp[s][s] = 1;
        for (auto i: adj[s])
            dp[s] |= dp[i];
    }
    for (int i = 1; i <= n; i++)
        cout << dp[i].count() << ' ';
}