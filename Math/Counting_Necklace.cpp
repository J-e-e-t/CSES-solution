/*Your task is to count the number of different necklaces that consist of n pearls and each pearl has m possible colors.

Two necklaces are considered to be different if it is not possible to rotate one of them so that they look the same.

Input

The only input line has two numbers n and m: the number of pearls and colors.

Output

Print one integer: the number of different necklaces modulo 109+7.

Constraints

    1≤n,m≤106


Example

Input:
4 3

Output:
24
*/

// This is computed by using Burnside’s Lemma. 
// https://www.geeksforgeeks.org/orbit-counting-theorem-or-burnsides-lemma/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD=1000000007; 
long long int inverse(long long int i){
    if(i==1) return 1;
    return (MOD - ((MOD/i)*inverse(MOD%i))%MOD+MOD)%MOD;
}

ll POW(ll a,ll b)
{
    if(b==0) return 1;
    if(b==1) return a%MOD;
    ll temp=POW(a,b/2);
    if(b%2==0) return (temp*temp)%MOD;
    else return (((temp*temp)%MOD)*a)%MOD;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n,m;
    cin>>n>>m;
    ll ans=0;
    for(ll i=0;i<n;i++)
    {
        ll temp=POW(m,__gcd(i,n));
        temp*=inverse(n);
        temp%=MOD;
        ans+=temp;
        ans%=MOD;
    }
    cout<<ans;
}