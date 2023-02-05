/*
Your task is to calculate the number of valid bracket sequences of length n when a prefix of the sequence is given.

Input

The first input line has an integer n.

The second line has a string of k characters: the prefix of the sequence.

Output

Print the number of sequences modulo 109+7.

Constraints

    1≤k≤n≤106


Example

Input:
6
(()

Output:
2

Explanation: There are two possible sequences: (())() and (()()). 
*/
//https://codeforces.com/blog/entry/87585

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
    string s;
    cin>>s;
    ll k=0,o=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='(') 
        {
            k++;
            o++;
        }
        else k--;
        if(k<0)
        {
            cout<<0;
            return 0;
        }
    }
    n-=o;
    if(k<0 || n<0 || 2*n+k<n)
    {
        cout<<0;
        return 0;
    }
    ll fact[2*n+k+1];
    fact[0]=1;
    for(int i=1;i<=2*n+k;i++)
    {
        fact[i]=(fact[i-1]*i)%MOD;
    }
    ll ans=(fact[2*n+k]*inverse(fact[n]))%MOD;
    ans*=inverse(fact[n+k]);
    ans%=MOD;
    ans*=((k+1)*inverse(n+k+1))%MOD;
    ans%=MOD;
    cout<<ans;
}