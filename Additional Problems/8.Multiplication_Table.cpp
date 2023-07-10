/*
Find the middle element when the numbers in an n×n multiplication table are sorted in increasing order. It is assumed that n is odd.

For example, the 3×3 multiplication table is as follows:
123
246
369

The numbers in increasing order are [1,2,2,3,3,4,6,6,9], so the answer is 3.

Input

The only input line has an integer n.

Output

Print one integer: the answer to the task.

Constraints

    1≤n<106


Example

Input:
3

Output:
3
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll N;

ll f(ll x){
    ll cnt = 0;
    for(ll i = 1; i <= N; i++)
        cnt += min(N, x/i);
    return cnt;
}

int main(){
    scanf("%lld", &N);
    ll lo = 0, hi = N*N;
    while(hi-lo > 1){
        ll mid = lo + (hi-lo)/2;
        if(f(mid) < (N*N+1)/2)  lo = mid;
        else                    hi = mid;
    }
    printf("%lld\n", lo+1);
}
