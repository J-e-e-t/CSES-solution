/*
You are given a string of length n and a dictionary containing k words. In how many ways can you create the string using the words?

Input

The first input line has a string containing n characters between a–z.

The second line has an integer k: the number of words in the dictionary.

Finally there are k lines describing the words. Each word is unique and consists of characters a–z.

Output

Print the number of ways modulo 109+7.

Constraints

    1≤n≤5000


1≤k≤105

the total length of the words is at most 106


Example

Input:
ababc
4
ab
abab
c
cb

Output:
2

Explanation: The possible ways are ab+ab+c and abab+c. */


/*
Problem Name: Word Combinations
Problem Link: https://cses.fi/problemset/task/1731
Author: Sachin Srivastava (mrsac7)
*/
#include<bits/stdc++.h>
using namespace std;

template<typename... T>
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {cerr << *it << "=" << a << ", "; err(++it, args...);}

#define int long long
#define F first
#define S second

const long long inf = 1LL<<62;
const int md = 1000000007;

int trie[1000005][26];
bool stop[1000005];
int dp[5005];
int ct = 0;
void insert(string s) {
    int node = 0;
    for (int i = 0; i < s.size(); i++) {
        if (!trie[node][s[i]-'a']) trie[node][s[i]-'a'] = ++ct;
        node = trie[node][s[i]-'a'];
    }
    stop[node] = 1;
}
string s;
int search(int x) {
    int node = 0, ans = 0;
    for (int i = x; i < s.size(); i++) {
        if (!trie[node][s[i]-'a']) return ans;
        node = trie[node][s[i] - 'a'];
        if (stop[node]) {
            (ans += dp[i+1])%=md;
        }
    }
    return ans;
}

void solve(){
    cin>>s;
    int k; cin>>k;
    while(k--) {
        string x; cin>>x;
        insert(x);
    }
    dp[s.size()] = 1;
    for (int i = s.size() - 1; i>=0; i--) {        
        dp[i] = search(i);
    }
    cout<<dp[0];
}    
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int t=1;
    //cin>>t;
    for (int i = 1; i <= t; i++) {
        solve();
        cout<<'\n';
    }
}