/*
Your task is to create a permutation of numbers 1,2,…,n that has exactly k inversions.

An inversion is a pair (a,b) where a<b and pa>pb where pi denotes the number at position i in the permutation.

Input

The only input line has two integers n and k.

Output

Print a line that contains the permutation. You can print any valid solution.

Constraints

    1≤n≤106


0≤k≤n(n−1)2


Example

Input:
5 4

Output:
1 5 2 4 3
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 1e6+1;

int N, idx, ans[maxN];
ll K;
deque<int> DQ;

int main(){
    scanf("%d %lld", &N, &K);
    for(int i = 1; i <= N; i++)
        DQ.push_back(i);

    for(int k = N-1; k >= 0; k--){
        if(k <= K){
            ans[++idx] = DQ.back();
            DQ.pop_back();
            K -= k;
        } else {
            ans[++idx] = DQ.front();
            DQ.pop_front();
        }
    }

    for(int i = 1; i <= idx; i++)
        printf("%d%c", ans[i], (" \n")[i==idx]);
}