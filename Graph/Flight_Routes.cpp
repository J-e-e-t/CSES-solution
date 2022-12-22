/*Your task is to find the k shortest flight routes from Syrjälä to Metsälä. A route can visit the same city several times.

Note that there can be several routes with the same price and each of them should be considered (see the example).

Input

The first input line has three integers n, m, and k: the number of cities, the number of flights, and the parameter k. The cities are numbered 1,2,…,n. City 1 is Syrjälä, and city n is Metsälä.

After this, the input has m lines describing the flights. Each line has three integers a, b, and c: a flight begins at city a, ends at city b, and its price is c. All flights are one-way flights.

You may assume that there are at least k distinct routes from Syrjälä to Metsälä.

Output

Print k integers: the prices of the k cheapest routes sorted according to their prices.

Constraints

    2≤n≤105


1≤m≤2⋅105

1≤a,b≤n

1≤c≤109

1≤k≤10


Example

Input:
4 6 3
1 2 1
1 3 3
2 3 2
2 4 6
3 2 8
3 4 1
*/

/*
Time Complexity: $\mathcal{O}(mk\log (mk))$

Maintain a priority queue of the $k$ best distances found for each vertex. We'll
iterate through the adjacency list of each vertex at most $k$ times.*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using db = double;
using str = string;
#define pb push_back
#define f first
#define s second


const int MX = 2e5+5;
int n,m,k;
priority_queue<ll> bes[MX];
vector<pair<ll,ll>> adj[MX];
priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    for(int i=0;i<m;i++) {
        int a,b,c; cin >> a >> b >> c;
        adj[a].pb({b,c});
    }
    bes[1].push(0); pq.push({0,1});
    while (pq.size()) {
        auto a = pq.top(); pq.pop();
        if (a.f > bes[a.s].top()) continue;
        for (auto& i: adj[a.s]) {
            ll tmp = a.f+i.s;
            if ((bes[i.f].size()) < k) {
                bes[i.f].push(tmp);
                pq.push({tmp,i.f});
            } else if (tmp < bes[i.f].top()) {
                bes[i.f].pop();
                bes[i.f].push(tmp);
                pq.push({tmp,i.f});
            }
        }
    }
    vector<ll> ans;
    while (bes[n].size()) {
        ans.push_back(bes[n].top());
        bes[n].pop();
    }
    reverse(ans.begin(),ans.end());
    for (auto a: ans) cout << a << " ";
}