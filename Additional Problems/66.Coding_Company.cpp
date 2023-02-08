/*
Your company has n coders, and each of them has a skill level between 0 and 100. Your task is to divide the coders into teams that work together.

Based on your experience, you know that teams work well when the skill levels of the coders are about the same. For this reason, the penalty for creating a team is the skill level difference between the best and the worst coder.

In how many ways can you divide the coders into teams such that the sum of the penalties is at most x?

Input

The first input line has two integers n and x: the number of coders and the maximum allowed penalty sum.

The next line has n integers t1,t2,…,tn: the skill level of each coder.

Output

Print one integer: the number of valid divisions modulo 109+7.

Constraints

    1≤n≤100


0≤x≤5000

0≤ti≤100


Example

Input:
3 2
2 5 3

Output:
3
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 101, maxX = 5e3+1;
const ll MOD = 1e9+7;

int N, X, t[maxN];
ll dp[maxN][maxN][maxX];

int main(){
    scanf("%d %d", &N, &X);
    for(int i = 1; i <= N; i++)
        scanf("%d", &t[i]);
    sort(t+1, t+N+1);
    t[0] = t[1];

    dp[0][0][0] = 1;
    for(int i = 1; i <= N; i++){
        for(int j = N; j >= 0; j--){
            for(int k = X; k >= 0; k--){
                ll cnt = dp[i-1][j][k];
                int newk = k + j * (t[i]-t[i-1]);
                if(newk > X)    continue;

                dp[i][j][newk] = (dp[i][j][newk] + (j+1) * cnt) % MOD;
                if(j != N)  dp[i][j+1][newk] = (dp[i][j+1][newk] + cnt) % MOD;
                if(j != 0)  dp[i][j-1][newk] = (dp[i][j-1][newk] + j * cnt) % MOD;
            }
        }
    }

    ll tot = 0;
    for(int i = 0; i <= X; i++)
        tot = (tot + dp[N][0][i]) % MOD;
    printf("%lld\n", tot);
}