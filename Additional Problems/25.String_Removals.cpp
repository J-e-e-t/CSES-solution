/*
You are given a string. You can remove any number of characters from it, but you cannot change the order of the remaining characters.

How many different strings can you generate?

Input

The first input line contains a string of size n. Each character is one of a–z.

Output

Print one integer: the number of strings modulo 109+7.

Constraints

    1≤n≤5⋅105


Example

Input:
aybabtu

Output:
103
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 500005;
const int md = 1e9+7;
int dp[mxN];
int ind[26];
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    string s; cin>>s;
    int n = s.size();
    memset(ind, -1, sizeof ind);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = 2*dp[i-1];
        if (ind[s[i-1]-'a'] >= 0)
            dp[i] -= dp[ind[s[i-1]-'a']];

        dp[i] = (dp[i] + md)%md;
        ind[s[i-1]-'a'] = i-1;
    }
    cout<<(dp[n]-1+md)%md;
}