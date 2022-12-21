/*
Byteland has n cities, and m roads between them. The goal is to construct new roads so that there is a route between any two cities.

Your task is to find out the minimum number of roads required, and also determine which roads should be built.
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

void dfs(ll node,vector<ll> &vis,ll comp,vector<vector<ll>> &graph,vector<ll> &nodes){
    nodes[node] = comp;
    vis[node] = 1;

    // cout<<"node "<<node<<" comp "<<comp<<endl;

    for(auto edge: graph[node]){
        if(vis[edge]==0){
            dfs(edge,vis,comp,graph,nodes);
        }
    }

    return;
}

void solve(){
    ll n,e;
    cin>>n>>e;

    ll a,b;

    vector<ll> nodes(n+1,0);
    vector<ll> vis(n+1,0);

    vector<vector<ll>> graph(n+1);

    for(ll i=0;i<e;i++){
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }


    ll comp = 0;

    vector<ll> comps;

    for(ll i=1;i<=n;i++){
        if(nodes[i]==0){
            comp++;
            comps.push_back(i);
            dfs(i,vis,comp,graph,nodes);
        }
    }
    // cout<<comp<<"here";

    // for(int i=1;i<=n;i++){
    //     cout<<nodes[i]<<" ";
    // }

    cout<<comps.size()-1<<endl;

    for(int i=1;i<comps.size();i++){
        cout<<comps[0]<<" "<<comps[i]<<endl;
    }
 
} 