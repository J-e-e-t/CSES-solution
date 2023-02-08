/*
Christmas Party

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

There are n
children at a Christmas party, and each of them has brought a gift. The idea is that everybody will get a gift brought by someone else.

In how many ways can the gifts be distributed?

Input

The only input line has an integer n: the number of children.

Output

Print the number of ways modulo 109+7.

Constraints

    1≤n≤106


Example

Input:
4

Output:
9
*/

/*
This is a standard problem of finding derangements in a sequence.
The recursive formula is  .
For info regarding derangement, see https://en.wikipedia.org/wiki/Derangement.
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin>>n;
    ll d[n+1];
    d[1]=0;
    d[2]=1;
    for(ll i=3;i<=n;i++)
    {
        d[i]=(((d[i-1]+d[i-2])%MOD)*(i-1))%MOD;
    }
    cout<<d[n];
}