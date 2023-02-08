/*
A directed graph consists of n nodes and m edges. The edges are numbered 1,2,…,n.

Your task is to answer q queries of the form "can you reach node b from node a?"

Input

The first input line has three integers n, m and q: the number of nodes, edges and queries.

Then there are m lines describing the edges. Each line has two distinct integers a and b: there is an edge from node a to node b.

Finally there are q lines describing the queries. Each line consists of two integers a and b: "can you reach node b from node a?"

Output

Print the answer for each query: either "YES" or "NO".

Constraints

    1≤n≤5⋅104


1≤m,q≤105


Example

Input:
4 4 3
1 2
2 3
3 1
4 3
1 3
1 4
4 1

Output:
YES
NO
YES
*/

#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define endl '\n'
 
const int mxN = 5e4+5;
vector<bitset<mxN>> dp(mxN);
vector<int> adj[mxN], adj2[mxN], cond[mxN];
vector<int> v;
int comp[mxN];
int cnt = 0;
int vis[mxN];
 
void dfs(int s, vector<int> adj[]) {
    if (vis[s]) return;
    vis[s] = 1;
    for (auto i: adj[s]) 
        dfs(i, adj);
    v.push_back(s);
}
 
void dfs2(int s, int cnt) {
    if (comp[s]) return;
    comp[s] = cnt;
    for (auto i: adj2[s]) 
        dfs2(i, cnt);
}
 

 
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n, m, t; cin >> n >> m >> t;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj2[y].push_back(x);
    }
    //topological sort
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i, adj);
    }
    //condensing SCCs
    reverse(v.begin(), v.end());
    for (auto i: v) {
        if (!comp[i]) {
            dfs2(i, ++cnt);
        }
    }
    //condesed graph.
    for (int i = 1; i <= n; i++) {
        for (auto j: adj[i]) if (comp[i] != comp[j]) {
            cond[comp[i]].push_back(comp[j]);
        }
    }
 
    memset(vis, 0, sizeof vis);
    v.clear();
    //topological sort of condensed graphs
    for (int i = 1; i <= cnt; i++) {
        if (!vis[i])
            dfs(i, cond);
    }
        
    for (auto s: v) {
        dp[s][s] = 1;
        for (auto i: cond[s])
            dp[s] |= dp[i];
    }

    while (t--) {
        int x, y; cin >> x >> y;
        cout << (dp[comp[x]][comp[y]] ? "YES" : "NO") << endl;
    }
    
}
