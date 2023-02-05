/*
Bracket Sequences I
Your task is to calculate the number of valid bracket sequences of length n. For example, when n=6, there are 5 sequences:

    ()()()
    ()(())
    (())()
    ((()))
    (()())

Input

The only input line has an integer n.

Output

Print the number of sequences modulo 109+7.

Constraints

    1≤n≤106


Example

Input:
6

Output:
5
*/


// You can refer to this — https://cp-algorithms.com/combinatorics/bracket_sequences.html

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD=1000000007; 
long long int inverse(long long int i){
    if(i==1) return 1;
    return (MOD - ((MOD/i)*inverse(MOD%i))%MOD+MOD)%MOD;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin>>n;
    if(n%2==1) 
    {
        cout<<0;
        return 0;
    }
    n/=2;
    ll fact[2*n+1];
    fact[0]=1;
    for(ll i=1;i<=2*n;i++)
    {
        fact[i]=(fact[i-1]*i)%MOD;
    }
    ll ans=(fact[2*n]*inverse(fact[n]))%MOD;
    ans*=(inverse(fact[n])*inverse(n+1))%MOD;
    ans%=MOD;
    cout<<ans;
}