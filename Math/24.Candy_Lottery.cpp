/*
There are n children, and each of them independently gets a random integer number of candies between 1 and k.

What is the expected maximum number of candies a child gets?

Input

The only input line contains two integers n and k.

Output

Print the expected number rounded to six decimal places.

Constraints

    1≤n≤100


1≤k≤100


Example

Input:
2 3

Output:
2.444444
*/

/*

For each i from 1 to k, we first find the probability such that the maximum is i. That would be equal to (i/k)^n − (i−1/k)^n. This is because we first uniformly choose n numbers from 1 to i and subtract those cases in which i doesn’t occur. Next we multiply it by i to find the expected maximum, and add all those.
Taking care of rounding off. See my code for that.
Time complexity is O(nk). 
*/



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
    ld ans=0;
    for(int i=1;i<=k;i++)
    {
        ld add=1,sub=1;
        for(int j=1;j<=n;j++)
        {
            add*=(ld)i/(ld)k;
            sub*=(ld)(i-1)/(ld)k;
        }
        ans+=(ld)(i)*(ld)(add-sub);
    }
    ans*=1e6;
    ans=llround(ans);
    ans/=1e6;
    cout<<fixed<<setprecision(6)<<ans;
}