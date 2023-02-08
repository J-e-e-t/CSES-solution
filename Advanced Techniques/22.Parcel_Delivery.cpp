/*
There are n cities and m routes through which parcels can be carried from one city to another city. For each route, you know the maximum number of parcels and the cost of a single parcel.

You want to send k parcels from Syrjälä to Lehmälä. What is the cheapest way to do that?

Input

The first input line has three integers n, m and k: the number of cities, routes and parcels. The cities are numbered 1,2,…,n. City 1 is Syrjälä and city n is Lehmälä.

After this, there are m lines that describe the routes. Each line has four integers a, b, r and c: there is a route from city a to city b, at most r parcels can be carried through the route, and the cost of each parcel is c.

Output

Print one integer: the minimum total cost or −1 if there are no solutions.

Constraints

    1≤n≤500


1≤m≤1000

1≤k≤100

1≤a,b≤n

1≤r,c≤1000


Example

Input:
4 5 3
1 2 5 100
1 3 10 50
1 4 7 500
2 4 8 350
3 4 2 100

Output:
750

Explanation: One parcel is delivered through route 1→2→4 (cost 1⋅450=450) and two parcels are delivered through route 1→3→4 (cost 2⋅150=300). 
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 501, maxM = 1001;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int N, M, K, p[maxN];
ll d[maxN], cap[maxN][maxN], cost[maxN][maxN];
bool inq[maxN];
vector<int> G[maxN];

struct Edge {
    int u, v;
    ll r, c;
} edges[maxM], redges[maxM];

void bellman_ford(){
    fill(inq+1, inq+N+1, false);
    fill(d+1, d+N+1, INF);
    fill(p+1, p+N+1, 0);

    queue<int> Q;
    Q.push(1);
    d[1] = 0;
    inq[1] = true;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        inq[u] = false;

        for(int i : G[u]){
            Edge e = (i < 0 ? redges[-i] : edges[i]);
            if(e.r > 0 && d[e.v] > d[u] + e.c){
                d[e.v] = d[u] + e.c;
                p[e.v] = i;
                if(!inq[e.v]){
                    inq[e.v] = true;
                    Q.push(e.v);
                }
            }
        }
    }
}

ll minimum_cost_flow(){
    ll flow = 0, cost = 0;
    while(flow < K){
        bellman_ford();
        if(d[N] == INF) break;

        ll aug = K-flow;
        int u = N;
        while(u != 1){
            Edge e = (p[u] < 0 ? redges[-p[u]] : edges[p[u]]);
            aug = min(aug, e.r);
            u = e.u;
        }

        flow += aug;
        cost += aug * d[N];
        u = N;
        while(u != 1){
            if(p[u] < 0){
                redges[-p[u]].r -= aug;
                edges[-p[u]].r += aug;
            } else {
                redges[p[u]].r += aug;
                edges[p[u]].r -= aug;
            }
            u = (p[u] < 0 ? redges[-p[u]].u : edges[p[u]].u);
        }
    }
    return (flow < K ? -1 : cost);
}

int main(){
    scanf("%d %d %d", &N, &M, &K);
    for(int i = 1, u, v, r, c; i <= M; i++){
        scanf("%d %d %d %d", &u, &v, &r, &c);
        G[u].push_back(i);
        G[v].push_back(-i);
        edges[i] = {u, v, r, c};
        redges[i] = {v, u, 0, -c};
    }
    printf("%lld\n", minimum_cost_flow());
}

