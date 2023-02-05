/*
Each square of an 8×8 chessboard has a robot. Each robot independently moves k steps, and there can be many robots on the same square.

On each turn, a robot moves one step left, right, up or down, but not outside the board. It randomly chooses a direction among those where it can move.

Your task is to calculate the expected number of empty squares after k turns.

Input

The only input line has an integer k.

Output

Print the expected number of empty squares rounded to six decimal places.

Constraints

    1≤k≤100


Example

Input:
10

Output:
23.120740
*/


/*

We do something like brute force here. Consider a robot on a single cell only, assuming all others don’t have robot present.
Here dp[k][i][j]  represents the expected probability of a robot to be present in cell   after   steps.
The state transition would be     , where   and   iterates over the   possible directions.
The expected answer for each individual cell   would be the product of  .
Adding all the expected values for a single cell gives us our final answer.
Time complexity is    . 
*/


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int MOD=1000000007;
using ld = long double;

ll dr[4]={1,-1,0,0};
ll dc[4]={0,0,1,-1};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin>>n;
    ld dp[n+1][8][8]={};
    ld ans[8][8];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            ans[i][j]=1;
        }
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            for(int k=0;k<=n;k++)
            {
                for(int i1=0;i1<8;i1++)
                {
                    for(int j1=0;j1<8;j1++)
                    {
                        dp[k][i1][j1]=0;
                    }
                }
            }
            dp[0][i][j]=1;
            for(int k=0;k<n;k++)
            {
                for(int i1=0;i1<8;i1++)
                {
                    for(int j1=0;j1<8;j1++)
                    {
                        ld dir=0;
                        for(int f=0;f<4;f++)
                        {
                            ll u=i1+dr[f],v=j1+dc[f];
                            if(u>=0 && u<8 && v>=0 && v<8)
                            {
                                dir++;
                            }
                        }
                        for(int f=0;f<4;f++)
                        {
                            ll u=i1+dr[f],v=j1+dc[f];
                            if(u>=0 && u<8 && v>=0 && v<8)
                            {
                                dp[k+1][u][v]+=dp[k][i1][j1]/dir;
                            }
                        }
                    }
                }
            }
            for(int i1=0;i1<8;i1++)
            {
                for(int j1=0;j1<8;j1++)
                {
                    ans[i1][j1]*=(1-dp[n][i1][j1]);
                }
            }
        }
    }
    ld expc=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            expc+=ans[i][j];
        }
    }
    cout<<fixed<<setprecision(6)<<expc;
}