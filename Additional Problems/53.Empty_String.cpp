/*
You are given a string consisting of n characters between a and z.

On each turn, you may remove any two adjacent characters that are equal. Your goal is to construct an empty string by removing all the characters.

In how many ways can you do this?

Input

The only input line has a string of length n.

Output

Print one integer: the number of ways modulo 109+7.

Constraints

    1≤n≤500


Example

Input:
aabccb

Output:
3
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 505;
const ll MOD = 1e9+7;

int N;
char S[maxN];
ll fac[maxN], inv[maxN], dp[maxN][maxN];

ll fastpow(ll x, ll b){
    ll res = 1;
    while(b){
        if(b&1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        b >>= 1;
    }
    return res;
}

ll choose(int n, int k){
    if(k < 0 || n < k)  return 0;
    return fac[n] * inv[k] % MOD * inv[n-k] % MOD;
}

void init(){
    fac[0] = inv[0] = 1;
    for(int i = 1; i < maxN; i++){
        fac[i] = (fac[i-1] * i) % MOD;
        inv[i] = fastpow(fac[i], MOD-2);
    }

    for(int i = 0; i < maxN; i++)
        for(int j = i; j < maxN; j++)
            dp[i][j] = -1;
}

ll solve(int l, int r){
    if((r-l+1)&1)       return 0;
    if(l > r)           return 1;
    if(dp[l][r] != -1)  return dp[l][r];

    ll cnt = 0;
    for(int m = l+1; m <= r; m++){
        if(S[l] == S[m]){
            ll subcases = solve(l+1, m-1) * solve(m+1, r) % MOD;
            ll aftercombine = subcases * choose((r-l+1)/2, (m-l+1)/2) % MOD;
            cnt = (cnt + aftercombine) % MOD;
        }
    }

    return dp[l][r] = cnt;
}

int main(){
    scanf(" %s", S);
    N = (int) strlen(S);
    init();
    printf("%lld\n", N&1 ? 0 : solve(0, N-1));
}