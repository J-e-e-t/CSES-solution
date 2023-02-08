/*
You are given an undirected graph that has n nodes and m edges.

We consider subgraphs that have all nodes of the original graph and some of its edges. A subgraph is called Eulerian if each node has even degree.

Your task is to count the number of Eulerian subgraphs modulo 109+7.

Input

The first input line has two integers n and m: the number of nodes and edges. The nodes are numbered 1,2,…,n.

After this, there are m lines that describe the edges. Each line has two integers a and b: there is an edge between nodes a and b. There is at most one edge between two nodes, and each edge connects two distinct nodes.

Output

Print the number of Eulerian subgraphs modulo 109+7.

Constraints

    1≤n≤105


0≤m≤2⋅105

1≤a,b≤n


Example

Input:
4 3
1 2
1 3
2 3

Output:
2

Explanation: You can either keep or remove all edges, so there are two possible Eulerian subgraphs. 
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 1e5+5;
const int md = 1e9+7;
vector<int> adj[mxN];
int vis[mxN];

int exp(int x, int y, int md){
    int ans = 1;
    x = x%md;
    while (y > 0) {
        if (y&1)
            ans = ans*x%md;
        y = y>>1;
        x = x*x%md;
    }
    return ans;
}

int cnt = 0;
void dfs(int s, int p) {
    if (vis[s]) return;
    vis[s] = 1;
    for (auto i: adj[s]) if (i != p) {
        if (vis[i] == 1) 
            cnt++;
        else if (vis[i] == 0)
            dfs(i, s);
    }
    vis[s] = 2;
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
        adj[y].push_back(x);
    }

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            cnt = 0;
            dfs(i, 0);
            ans = ans * exp(2, cnt, md) % md;
        }
    }

    cout << ans;
}