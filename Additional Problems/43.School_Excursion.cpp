/*
A group of n children are coming to Helsinki. There are two possible attractions: a child can visit either Korkeasaari (zoo) or Linnanmäki (amusement park).

There are m pairs of children who want to visit the same attraction. Your task is to find all possible alternatives for the number of children that will visit Korkeasaari. The children's wishes have to be taken into account.

Input

The first input line has two integers n and m: the number of children and their wishes. The children are numbered 1,2,…,n.

After this, there are m lines describing the children's wishes. Each line has two integers a and b: children a and b want to visit the same attraction.

Output

Print a bit string of length n where a one-bit at index i indicates that it is possible that exactly i children visit Korkeasaari (the bit string is to be considered one-indexed).

Constraints

    1≤n≤105


0≤m≤105

1≤a,b≤n


Example

Input:
5 3
1 2
2 3
1 5

Output:
10011

Explanation: The number of children visiting Korkeasaari can be 1, 4 or 5. 
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e5+1;

int N, M, a, b, ds[maxN];
multiset<int> sizes;
bitset<maxN> dp;

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
    scanf("%d %d", &N, &M);
    fill(ds+1, ds+N+1, -1);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        merge(a, b);
    }

    for(int i = 1; i <= N; i++)
        if(find(i) == i)
            sizes.insert(-ds[i]);

    dp[0] = 1;
    for(int sz : sizes)
        dp |= (dp<<sz);

    for(int i = 1; i <= N; i++)
        printf("%d", dp[i] ? 1 : 0);
    printf("\n");
}
