/*
There are n cities and initially no roads between them. However, every day a new road will be constructed, and there will be a total of m roads.

A component is a group of cities where there is a route between any two cities using the roads. After each day, your task is to find the number of components and the size of the largest component.

Input

The first input line has two integers n and m: the number of cities and roads. The cities are numbered 1,2,…,n.

Then, there are m lines describing the new roads. Each line has two integers a and b: a new road is constructed between cities a and b.

You may assume that every road will be constructed between two different cities.

Output

Print m lines: the required information after each day.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
5 3
1 2
1 3
4 5

Output:
4 2
3 3
2 3
*/
#include <bits/stdc++.h>
using namespace std;

int total_comp;
int maxs;
vector<int> par;
vector<int> sz;

int rep(int x){
    if(par[x]==x){
        return x;
    }else{
        return par[x] = rep(par[x]);
    }
}

bool unite(int a,int b){
    int ra = rep(a);
    int rb = rep(b);
    if(ra == rb){
        return false;
    }
    if(sz[ra]>sz[rb]){
        swap(a,b);
    }
    sz[rb]+=sz[ra];
    par[ra] = rb;
    // maxs = max(maxs,sz[b]);
    if(sz[rb]>maxs){
        maxs=sz[rb];
    }    
    return true;
}
void solve(){
    int n,q;
    cin>>n>>q;
    total_comp = n;
    maxs =1;
    par.resize(n);
    sz.resize(n);
    for(int i=0;i<n;i++){
        par[i]=i;
        sz[i] =1;
    }
    
    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        a--;
        b--;

        if(unite(a,b)){
            total_comp--;
            cout<<total_comp<<" "<<maxs<<"\n";

        }else{
            cout<<total_comp<<" "<<maxs<<"\n";
        }


    }

}

int main(){
    solve();
}
