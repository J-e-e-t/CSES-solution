/*
Your task is to count the number of one bits in the binary representations of integers between 1 and n.

Input

The only input line has an integer n.

Output

Print the number of one bits in the binary representations of integers between 1 and n.

Constraints

    1≤n≤1015


Example

Input:
7

Output:
12

Explanation: The binary representations of 1…7 are 1, 10, 11, 100, 101, 110, and 111, so there are a total of 12 one bits. */

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n; cin>>n;
    int dp[50] = {0};
    dp[0] = 1;
    for (int i = 1; i < 50; i++) 
        dp[i] = 2*dp[i-1] + ((1LL<<(i-1)) - 1);
    int ans = 0;
    while(n>0) {
        int b = log2(n);
        ans += dp[b];
        b = 1LL<<b;
        ans += n - b;
        n = n - b;
    }
    cout<<ans;
}
