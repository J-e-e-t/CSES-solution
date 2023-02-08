/*
Syrjälä's network has n computers and m connections between them. The network consists of components of computers that can send messages to each other.

Nobody in Syrjälä understands how the network works. For this reason, if a connection breaks down, nobody will repair it. In this situation a component may be divided into two components.

Your task is to calculate the number of components after each connection breakdown.

Input

The first input line has three integers n, m and k: the number of computers, connections and breakdowns. The computers are numbered 1,2,…,n.

Then, there are m lines describing the connections. Each line has two integers a and b: there is a connection between computers a and b. Each connection is between two different computers, and there is at most one connection between two computers.

Finally, there are k lines describing the breakdowns. Each line has two integers a and b: the connection between computers a and b breaks down.

Output

After each breakdown, print the number of components.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤k≤m

1≤a,b≤n


Example

Input:
5 5 3
1 2
1 3
2 3
3 4
4 5
3 4
2 3
4 5

Output:
2 2 3
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e5+1;
const int maxM = 2e5;
typedef pair<int,int> pii;

int N, M, K, a, b, cnt, ds[maxN], ans[maxM];
pii edges[maxM], queries[maxM];
set<pii> S;

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

int main(){
    scanf("%d %d %d", &N, &M, &K);
    fill(ds+1, ds+N+1, -1);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        if(b > a)   swap(a, b);
        edges[i] = {a, b};
    }
    for(int i = 0; i < K; i++){
        scanf("%d %d", &a, &b);
        if(b > a)   swap(a, b);
        queries[i] = {a, b};
        S.insert({a, b});
    }

    cnt = N;
    for(int i = 0; i < M; i++)
        if(S.find(edges[i]) == S.end())
            if(merge(edges[i].first, edges[i].second))
                cnt--;

    for(int i = K-1; i >= 0; i--){
        ans[i] = cnt;
        if(merge(queries[i].first, queries[i].second))
            cnt--;
    }

    for(int i = 0; i < K; i++)
        printf("%d%c", ans[i], (" \n")[i==K-1]);
}
