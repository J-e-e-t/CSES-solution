/*
Your task is to count the number of permutations of 1,2,…,n that have exactly k inversions (i.e., pairs of elements in the wrong order).

For example, when n=4 and k=3, there are 6 such permutations:

    [1,4,3,2]


[2,3,4,1]

[2,4,1,3]

[3,1,4,2]

[3,2,1,4]

[4,1,2,3]


Input

The only input line has two integers n and k.

Output

Print the answer modulo 109+7.

Constraints

    1≤n≤500


0≤k≤n(n−1)2


Example

Input:
4 3

Output:
6
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 501;
const int maxK = maxN*(maxN-1)/2;
const ll MOD = 1e9+7;

int N, K;
ll dp[maxN][maxK];

void init(){
    for(int i = 1; i < maxN; i++){
        int r = i*(i-1)/2;
        dp[i][0] = dp[i][r] = 1;
        for(int j = 1; j <= r/2; j++){
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
            if(j-i >= 0)
                dp[i][j] = (dp[i][j] - dp[i-1][j-i] + MOD) % MOD;
        }
        for(int j = r/2+1; j < r; j++)
            dp[i][j] = dp[i][r-j];
    }
}

int main(){
    init();
    scanf("%d %d", &N, &K);
    printf("%lld\n", dp[N][K]);
}