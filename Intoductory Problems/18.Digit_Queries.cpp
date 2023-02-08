/*
Consider an infinite string that consists of all positive integers in increasing order:

12345678910111213141516171819202122232425...

Your task is to process q queries of the form: what is the digit at position k in the string?

Input

The first input line has an integer q: the number of queries.

After this, there are q lines that describe the queries. Each line has an integer k: a 1-indexed position in the string.

Output

For each query, print the corresponding digit.

Constraints

    1≤q≤1000


1≤k≤1018


Example

Input:
3
7
19
12

Output:
7
4
1
*/


#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

int xpow(int x, unsigned int y){
    int res=1;
    while(y>0){
        if (y&1) res= (res*x); y=y>>1; x=(x*x);
    }
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int t; cin>>t;
    while(t--) {
        int n; cin>>n;
        int c = 1;
        for (int p = 9;; n -= p, c++, p = 9*xpow(10, c-1)*c) {
            if (n - p <= 0) break;
        }
        n--;
        int x = n/c;
        int y = n%c;
        int ans = xpow(10, c-1) + x;
        // cerr<<ans<<' '<<x<<' '<<y<<' '<<n<<' '<<c;
        string s = to_string(ans);
        cout<<s[y]<<endl;
    }
}