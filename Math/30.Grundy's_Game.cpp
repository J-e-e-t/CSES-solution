/*
There is a heap of n coins and two players who move alternately. On each move, a player chooses a heap and divides into two nonempty heaps that have a different number of coins. The player who makes the last move wins the game.

Your task is to find out who wins if both players play optimally.

Input

The first input line contains an integer t: the number of tests.

After this, there are t lines that describe the tests. Each line has an integer n: the number of coins in the initial heap.

Output

For each test case, print "first" if the first player wins the game and "second" if the second player wins the game.
*/
/*
We find the Sprague-Grundy values corresponding to the Grundy’s game. This can be easily done by dynamic programming, as we find the mex of all the state reachable from that state. Also we note that for larger values of n (n≥2000), its Sprague-Grundy value is never 0. (I don’t have a proof for this, maybe someone can let me know in the comments.)
You can read about Sprague-Grundy theorem here — https://cp-algorithms.com/game_theory/sprague-grundy-nim.html
*/


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int MOD=1000000007;
using ld = long double;


ll mex(vll v)
{
    set<ll> s;
    for(int i=0;i<v.size();i++)
    {
        s.insert(v[i]);
    }
    for(int i=0;i<1000001;i++)
    {
        if(s.count(i)==0) return i;
    }
}
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll limit=2000;
    ll dp[limit];
    dp[0]=dp[1]=dp[2]=0;
    for(int i=3;i<limit;i++)
    {
        vll v;
        for(int j=1;2*j<i;j++)
        {
            v.push_back(dp[j]^dp[i-j]);
        }
        dp[i]=mex(v);
    }
    ll t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        ll n;
        cin>>n;
        if(n>=limit) cout<<"first";
        else if(dp[n]==0) cout<<"second";
        else cout<<"first";
        cout<<"\n";
    }
}