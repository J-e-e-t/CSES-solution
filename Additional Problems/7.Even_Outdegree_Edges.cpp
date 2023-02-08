/*
Given an undirected graph, your task is to choose a direction for each edge so that in the resulting directed graph each node has an even outdegree. The outdegree of a node is the number of edges coming out of that node.

Input

The first input line has two integers n and m: the number of nodes and edges. The nodes are numbered 1,2,…,n.

After this, there are m lines describing the edges. Each line has two integers a and b: there is an edge between nodes a and b.

You may assume that the graph is simple, i.e., there is at most one edge between any two nodes and every edge connects two distinct nodes.

Output

Print m lines describing the directions of the edges. Each line has two integers a and b: there is an edge from node a to node b. You can print any valid solution.

If there are no solutions, only print "IMPOSSIBLE".

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
4 4
1 2
2 3
3 4
1 4

Output:
1 2
3 2
3 4
1 4
*/
#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int maxN = 1e5+5, maxM = 2e5+5;

int N, M, timer, in[maxN];
bool even[maxN];
vector<pii> G[maxN];
pii ans[maxM];

void dfs(int u, int p = -1){
    in[u] = ++timer;
    for(pii e : G[u]){
        int v = e.first, id = e.second;
        if(v != p){
            if(!in[v]){
                dfs(v, u);
                if(even[v]){
                    ans[id] = {u, v};
                    even[u] ^= true;
                } else {
                    ans[id] = {v, u};
                    even[v] ^= true;
                }
            } else if(in[v] < in[u]){
                even[u] ^= true;
                ans[id] = {u, v};
            }
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

    fill(even+1, even+N+1, true);
    for(int i = 1; i <= N; i++)
        if(!in[i])
            dfs(i);

    bool good = true;
    for(int i = 1; i <= N; i++)
        good &= even[i];

    if(good){
        for(int i = 0; i < M; i++)
            printf("%d %d\n", ans[i].first, ans[i].second);
    } else printf("IMPOSSIBLE\n");
}