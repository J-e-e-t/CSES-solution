/*
There are n cities with airports but no flight connections. You are given m requests which routes should be possible to travel.

Your task is to determine the minimum number of one-way flight connections which makes it possible to fulfil all requests.

Input

The first input line has two integers n and m: the number of cities and requests. The cities are numbered 1,2,…,n.

After this, there are m lines describing the requests. Each line has two integers a and b: there has to be a route from city a to city b. Each request is unique.

Output

Print one integer: the minimum number of flight connections.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
4 5
1 2
2 3
2 4
3 1
3 4

Output:
4

Explanation: You can create the connections 1→2, 2→3, 2→4 and 3→1. Then you can also fly from city 3 to city 4 using the route 3→1→2→4. */
#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e5+1;

int N, M, ds[maxN], vis[maxN];
vector<int> G[maxN], CC[maxN];

int find(int u){
    if(ds[u] < 0)   return u;
    ds[u] = find(ds[u]);
    return ds[u];
}

bool merge(int u, int v){
    u = find(u); v = find(v);
    if(u == v)  return false;
    if(ds[u] < ds[v])   swap(u, v);
    ds[v] += ds[u];
    ds[u] = v;
    return true;
}

bool dfs(int u){
    vis[u] = -1;
    bool hascycle = false;
    for(int v : G[u]){
        if(vis[v] == -1)        return true;
        else if(vis[v] == 0)    hascycle |= dfs(v);
    }
    vis[u] = 1;
    return hascycle;
}

int main(){
    scanf("%d %d", &N, &M);

    fill(ds+1, ds+N+1, -1);
    for(int i = 0, a, b; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        merge(a, b);
    }

    int K = 0;
    unordered_map<int,int> getID;
    for(int u = 1; u <= N; u++){
        int rep = find(u);
        if(!getID[rep])
            getID[rep] = ++K;
        CC[getID[rep]].push_back(u);
    }

    int ans = 0;
    for(int k = 1; k <= K; k++){
        int sz = (int) CC[k].size();
        bool hascycle = false;
        for(int u : CC[k])
            if(!hascycle && vis[u] == 0)
                hascycle |= dfs(u);
        ans += (hascycle ? sz : sz-1);
    }
    printf("%d\n", ans);
}