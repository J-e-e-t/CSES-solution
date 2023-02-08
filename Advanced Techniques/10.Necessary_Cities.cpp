/*
There are n cities and m roads between them. There is a route between any two cities.

A city is called necessary if there is no route between some other two cities after removing that city (and adjacent roads). Your task is to find all necessary cities.

Input

The first input line has two integers n and m: the number of cities and roads. The cities are numbered 1,2,…,n.

After this, there are m lines that describe the roads. Each line has two integers a and b: there is a road between cities a and b. There is at most one road between two cities, and every road connects two distinct cities.

Output

First print an integer k: the number of necessary cities. After that, print a list of k cities. You may print the cities in any order.

Constraints

    2≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
5 5
1 2
1 4
2 4
3 5
4 5

Output:
2
4 5
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 1e5+5;
vector<int> adj[mxN];
int ans[mxN];
int vis[mxN], low[mxN];
int cnt = 0;

void dfs(int s, int p) {
    vis[s] = ++cnt;
    low[s] = vis[s];
    int ch = 0; //children connected with tree-edge
    for (auto i: adj[s]) {
        if (i != p) {
            if (vis[i]) //back edge
                low[s] = min(low[s], vis[i]);
            else {
                dfs(i, s);
                low[s] = min(low[s], low[i]);
                if (p != 0 && low[i] >= vis[s])
                    ans[s] = 1;
                ch++;
            }
        }
    }
    if (p == 0 && ch > 1)
        ans[s] = 1;
}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n, m; cin>>n>>m;
    for (int i = 0; i < m; i++) {
        int x, y; cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i, 0);
    }
    cout<<accumulate(ans, ans+n+1, 0)<<endl;
    for (int i = 1; i <= n; i++) if (ans[i])
        cout<<i<<' ';
}
