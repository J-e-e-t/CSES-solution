/*
Your task is to create a permutation of numbers 1,2,…,n whose longest monotone subsequence has exactly k elements.

A monotone subsequence is either increasing or decreasing. For example, some monotone subsequences in [2,1,4,5,3] are [2,4,5] and [4,3].

Input

The first input line has an integer t: the number of tests.

After this, there are t lines. Each line has two integers n and k.

Output

For each test, print a line that contains the permutation. You can print any valid solution. If there are no solutions, print "IMPOSSIBLE".

Constraints

    1≤t≤1000


1≤k≤n≤100


Example

Input:
3
5 3
5 2
7 7

Output:
2 1 4 5 3
IMPOSSIBLE
1 2 3 4 5 6 7
*/
#include <bits/stdc++.h>

using namespace std;

int N, K;

void solve(){
    scanf("%d %d", &N, &K);
    if(K*K < N){
        printf("IMPOSSIBLE\n");
        return;
    }

    vector<int> ans;
    int l = 1, r = K;
    while(true){
        for(int i = r; i >= l; i--)
            ans.push_back(i);
        if(r == N)  break;
        l = r+1;
        r = min(r+K, N);
    }

    for(int i = 0; i < N; i++)
        printf("%d%c", ans[i], (" \n")[i==N-1]);
}

int main(){
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++){
        solve();
    }
}