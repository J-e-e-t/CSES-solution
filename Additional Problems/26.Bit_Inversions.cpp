/*
There is a bit string consisting of n bits. Then, there are some changes that invert one given bit. Your task is to report, after each change, the length of the longest substring whose each bit is the same.

Input

The first input line has a bit string consisting of n bits. The bits are numbered 1,2,…,n.

The next line contains an integer m: the number of changes.

The last line contains m integers x1,x2,…,xm describing the changes.

Output

After each change, print the length of the longest substring whose each bit is the same.

Constraints

    1≤n≤2⋅105


1≤m≤2⋅105

1≤xi≤n


Example

Input:
001011
3
3 2 5

Output:
4 2 3

Explanation: The bit string first becomes 000011, then 010011, and finally 010001. 
*/#include <bits/stdc++.h>

using namespace std;
const int maxN = 2e5+5;
const int SIZE = 4*maxN;

int N, M, mp[maxN], lo[SIZE], hi[SIZE], dp[3][SIZE];
char S[maxN];

int len(int i){
    return hi[i]-lo[i]+1;
}

int combine(int a, int b){
    return ((a<0)^(b<0)) ? a : a+b;
}

bool allsame(int i){
    return abs(dp[2][i]) == len(i);
}

void pull(int i){
    dp[0][i] = (allsame(2*i) ? combine(dp[0][2*i], dp[0][2*i+1]) : dp[0][2*i]);
    dp[1][i] = (allsame(2*i+1) ? combine(dp[1][2*i+1], dp[1][2*i]) : dp[1][2*i+1]);
    dp[2][i] = max(abs(combine(dp[1][2*i], dp[0][2*i+1])), max(dp[2][2*i], dp[2][2*i+1]));
}

void init(int i, int l, int r){
    lo[i] = l; hi[i] = r;
    if(l == r){
        mp[l] = i;
        dp[0][i] = dp[1][i] = (S[l-1] == '0' ? -1 : 1);
        dp[2][i] = abs(dp[0][i]);
        return;
    }
    int m = (l+r)/2;
    init(2*i, l, m);
    init(2*i+1, m+1, r);
    pull(i);
}

void update(int idx){
    int i = mp[idx];
    dp[0][i] *= -1;
    dp[1][i] = dp[0][i];

    i >>= 1;
    while(i){
        pull(i);
        i >>= 1;
    }
}

int query(){
    return dp[2][1];
}

int main(){
    scanf("%s %d", S, &M);
    N = (int) strlen(S);
    init(1, 1, N);
    for(int i = 0, x; i < M; i++){
        scanf("%d", &x);
        update(x);
        printf("%d%c", query(), (" \n")[i==M-1]);
    }
}
