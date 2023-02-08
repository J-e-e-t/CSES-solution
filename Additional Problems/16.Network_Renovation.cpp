/*
Syrjälä's network consists of n computers and n−1 connections between them. It is possible to send data between any two computers.

However, if any connection breaks down, it will no longer be possible to send data between some computers. Your task is to add the minimum number of new connections in such a way that you can still send data between any two computers even if any single connection breaks down.

Input

The first input line has an integer n: the number of computers. The computers are numbered 1,2,…,n.

After this, there are n−1 lines describing the connections. Each line has two integers a and b: there is a connection between computers a and b.

Output

First print an integer k: the minimum number of new connections. After this, print k lines describing the connections. You can print any valid solution.

Constraints

    3≤n≤105


1≤a,b≤n


Example

Input:
5
1 2
1 3
3 4
3 5

Output:
2
2 4
4 5
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e5+1;

int N, K;
vector<int> leaves, G[maxN];

void dfs(int u = 1, int p = -1){
    if((int) G[u].size() == 1)  leaves.push_back(u);
    for(int v : G[u])
        if(v != p)
            dfs(v, u);
}

int main(){
    scanf("%d", &N);
    for(int i = 0, a, b; i < N-1; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs();

    int K = (int) leaves.size();
    printf("%d\n", (K+1)/2);
    for(int i = 0; i < (K+1)/2; i++)
        printf("%d %d\n", leaves[i], leaves[i+K/2]);
}