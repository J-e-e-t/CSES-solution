/*
An array has n integers x1,x2,…,xn, and each of them has been randomly chosen between 1 and ri. An inversion is a pair (a,b) where a<b and xa>xb.

What is the expected number of inversions in the array?

Input

The first input line contains an integer n: the size of the array.

The second line contains n integers r1,r2,…,rn: the range of possible values for each array position.

Output

Print the expected number of inversions rounded to six decimal places.

Constraints

    1≤n≤100


1≤ri≤100


Example

Input:
3
5 2 7

Output:
1.057143
*/

/*
Due to lower constraint on  , brute force will work. We find expected inversions for every pair of (i,j)  where i<j 
f a[j]<=a[i] , then the number of inversions will be  a[j]c2 because  i-th element should have values till a[j].
Otherwise if a[j]>a[i]  then the number of inversions will be a[i]c2 + ((a[j]-a[i])*a[i]) , which is the sum of cases when  j-th element is less than a[i]or greater.

Time complexity is O(N^2)*/


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
    ll n;
    cin>>n;
    ll a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    ld ans=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            ll k;
            if(a[j]<=a[i])
            {
                k=(a[j]*(a[j]-1))/2;
            }
            else
            {
                k=(a[i]*(a[i]-1))/2 + (a[j]-a[i])*a[i];
            }
            ans+=(ld)k/(ld)(a[j]*a[i]);
        }
    }
    cout<<fixed<<setprecision(6)<<ans;
}