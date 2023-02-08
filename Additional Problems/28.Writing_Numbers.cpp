/*
     Time limit: 1.00 s Memory limit: 512 MB 

You would like to write a list of positive integers 1,2,3,… using your computer. However, you can press each key 0–9 at most n times during the process.

What is the last number you can write?

Input

The only input line contains the value of n.

Output

Print the last number you can write.

Constraints

    1≤n≤1018


Example

Input:
5

Output:
12

Explanation: You can write the numbers 1,2,…,12. This requires that you press key 1 five times, so you cannot write the number 13. 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll p[19];

void init(){
    p[0] = 1;
    for(int i = 1; i <= 18; i++)
        p[i] = p[i-1] * 10;
}

ll check(ll N){
    ll cnt = 0, l = N, r = 0;
    for(int i = 0; l; i++){
        int d = l % 10;
        l /= 10;
        cnt += (d == 1 ? l*p[i]+r+1 : (l+(d!=0))*p[i]);
        r += p[i] * d;
    }
    return cnt;
}

int main(){
    ll K;
    scanf("%lld", &K);
    ll lo = 1, hi = 1e18;
    init();
    while(hi-lo > 1){
        ll mid = lo+(hi-lo)/2;
        if(check(mid) <= K) lo = mid;
        else                hi = mid;
    }
    printf("%lld\n", lo);
}