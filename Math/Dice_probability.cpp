/*
You throw a dice n times, and every throw produces an outcome between 1 and 6. What is the probability that the sum of outcomes is between a and b?

Input

The only input line contains three integers n, a and b.

Output

Print the probability rounded to six decimal places.

Constraints

    1≤n≤100


1≤a≤b≤6n


Example

Input:
2 9 10

Output:
0.194444
*/

/*
This can be solved using dp, where  dp[i][j] denotes the probability of getting sum  j when the dice has been rolled  i times.
The transition would be-
 dp[i][j] =  summation (dp[i-1][j-k]) / 6 where k is (1,, min(6,j))
Then the answer will be    summation of dp[n][i] for all i ={a,,,b} .
Taking care of rounding off. See my code for that.
Time complexity is   O(n^2)*/



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
    ll n,a,b;
    cin>>n>>a>>b;
    vector<vector<ld> > dp(n+1,vector<ld> (6*n+1,0));
    dp[0][0]=1.0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=6*n;j++)
        {
            for(int k=1;k<=6;k++)
            {
                if(j-k>=0)
                {
                    dp[i][j]+=dp[i-1][j-k];
                }
            }
            dp[i][j]=dp[i][j]/6;
        }
    }
    ld ans=0;
    for(int i=a;i<=b;i++)
    {
        ans+=dp[n][i];
    }
    ans*=1e6;
    ans=llround(ans);
    ans/=1e6;
    cout<<fixed<<setprecision(6)<<ans;
}