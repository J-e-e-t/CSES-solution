/*
Given an undirected graph, your task is to choose a direction for each edge so that the resulting directed graph is strongly connected.

Input

The first input line has two integers n and m: the number of nodes and edges. The nodes are numbered 1,2,…,n.

After this, there are m lines describing the edges. Each line has two integers a and b: there is an edge between nodes a and b.

You may assume that the graph is simple, i.e., there are at most one edge between two nodes and every edge connects two distinct nodes.

Output

Print m lines describing the directions of the edges. Each line has two integers a and b: there is an edge from node a to node b. You can print any valid solution.

If there are no solutions, only print "IMPOSSIBLE".

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
3 3
1 2
1 3
2 3

Output:
1 2
2 3
3 1*/

#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int maxN = 1e5+1;
const int maxM = 2e5+1;

int N, M, timer, tin[maxN], low[maxN];
bool bridge_exists, vis[maxN], used[maxM];
vector<pii> G[maxN];
pii edges[maxM];

void dfs(int u = 1, int p = 0){
    vis[u] = true;
    tin[u] = low[u] = ++timer;
    for(pii P : G[u]){
        int v = P.first;
        int id = P.second;
        if(used[id])    continue;

        used[id] = true;
        edges[id] = {u, v};

        if(vis[v]){
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u])
                bridge_exists = true;
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0, a, b; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back({b, i});
        G[b].push_back({a, i});
    }

    dfs();
    if(timer == N && !bridge_exists){
        for(int i  = 0; i < M; i++)
            printf("%d %d\n", edges[i].first, edges[i].second);
    } else printf("IMPOSSIBLE\n");
}
