/*
You are given a cyclic array consisting of n values. Each element has two neighbors; the elements at positions n and 1 are also considered neighbors.

Your task is to divide the array into subarrays so that the sum of each subarray is at most k. What is the minimum number of subarrays?

Input

The first input line contains integers n and k.

The next line has n integers x1,x2,…,xn: the contents of the array.

There is always at least one division (i.e., no value in the array is larger than k).

Output

Print one integer: the minimum number of subarrays.

Constraints

    1≤n≤2⋅105


1≤xi≤109

1≤k≤1018


Example

Input:
8 5
2 2 2 1 3 1 2 1

Output:
3

Explanation: We can create three subarrays: [2,2,1], [3,1], and [2,1,2] (remember that the array is cyclic). 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 2e5+1;

int N, last[maxN];
ll K, x[2*maxN];

int main(){
    scanf("%d %lld", &N, &K);
    for(int i = 0; i < N; i++){
        scanf("%lld", &x[i]);
        x[i+N] = x[i];
    }

    int r = 0;
    ll sum = 0;
    for(int l = 0; l < N; l++){
        while(r < l+N && sum + x[r] <= K){
            sum += x[r];
            r++;
        }
        last[l] = r % N;
        sum -= x[l];
    }

    int opt = 0;
    for(int i = 0; i < N; i++)
        opt = last[opt];

    int cnt = 1;
    sum = x[opt];
    for(int i = opt+1; i < N+opt; i++){
        if(sum + x[i] <= K) sum += x[i];
        else {
            sum = x[i];
            cnt++;
        }
    }

    printf("%d\n", cnt);
}