/*
Consider a game where two players remove sticks from a heap. The players move alternately, and the player who removes the last stick wins the game.

A set P={p1,p2,…,pk} determines the allowed moves. For example, if P={1,3,4}, a player may remove 1, 3 or 4 sticks.

Your task is find out for each number of sticks 1,2,…,n if the first player has a winning or losing position.

Input

The first input line has two integers n and k: the number of sticks and moves.

The next line has k integers p1,p2,…,pk that describe the allowed moves. All integers are distinct, and one of them is 1.

Output

Print a string containing n characters: W means a winning position, and L means a losing position.

Constraints

    1≤n≤106


1≤k≤100

1≤pi≤n


Example

Input:
10 3
1 3 4

Output:
WLWWWWLWLW*/

/*

Let dp[i]  denote the result of game if there are total i sticks.

Here dp[i] is true is first player wins, otherwise false.
We know  dp[0] is false. The transition would be that if  dp[i-p[j]]  is false where j=1,,,,,k , then dp[i]  would be true.
Time complexity is O(n*k) . */


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int MOD=1000000007;
using ld = long double;


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n,k;
    cin>>n>>k;
    ll p[k];
    for(int i=0;i<k;i++)
    {
        cin>>p[i];
    }
    ll dp[n+1]={};
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<k;j++)
        {
            if(i-p[j]>=0 && dp[i-p[j]]==0)
            {
                dp[i]=1;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(dp[i]==1) cout<<"W";
        else cout<<"L";
    }
}