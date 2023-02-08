/*
You are given k distinct prime numbers a1,a2,…,ak and an integer n.

Your task is to calculate how many of the first n positive integers are divisible by at least one of the given prime numbers.

Input

The first input line has two integers n and k.

The second line has k prime numbers a1,a2,…,ak.

Output

Print one integer: the number integers within the interval 1,2,…,n that are divisible by at least one of the prime numbers.

Constraints

    1≤n≤1018


1≤k≤20

2≤ai≤n


Example

Input:
20 2
2 5

Output:
12

Explanation: the 12 numbers are 2,4,5,6,8,10,12,14,15,16,18,20. 
*/
/*
We will be using Inclusion-Exclusion principle, considering all subsets of given prime numbers. The count of numbers divisible by the subset of primes would be  n/prod   , where  prod  is the product of the subset of primes. The sign would be positive if the size of subset is odd, and negative otherwise.*/


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long MOD = 1e9 + 7;
using vll = vector<ll>;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n,k;
    cin>>n>>k;
    ll a[k];
    for(int i=0;i<k;i++)
    {
        cin>>a[i];
    }
    ll ans=0;
    for(int i=0;i<(1ll<<k);i++)
    {
        vll v;
        for(int j=0;j<k;j++)
        {
            if((i&(1<<j))!=0)
            {
                v.push_back(a[j]);
            }
        }
        ll prod=1;
        for(int j=0;j<v.size();j++)
        {
            if(prod>n/v[j])
            {
                prod=n+1;
                break;
            }
            prod*=v[j];
        }
        if(v.size()%2==0) ans-=n/prod;
        else ans+=n/prod;
    }
    ans+=n;
    cout<<ans;
}