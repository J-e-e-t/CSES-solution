/*
You are given an array of n positive integers. Your task is to find two integers such that their greatest common divisor is as large as possible.

Input

The first input line has an integer n: the size of the array.

The second line has n integers x1,x2,…,xn: the contents of the array.

Output

Print the maximum greatest common divisor.

Constraints

    2≤n≤2⋅105


1≤xi≤106


Example

Input:
5
3 14 15 7 9

Output:

*/

/*
We have to basically find the largest divisor such that it divides atleast 2 numbers in the array x . So we iterate from the max possible answer i.e 1e6 to 1, , and increase the divisor count if the number is present in array. Time complexity is  O(nlogn)*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin>>n;
    ll x[n];
    ll cnt[1000001]={};
    for(int i=0;i<n;i++)
    {
        cin>>x[i];
        cnt[x[i]]++;
    }
    for(int i=1000000;i>=1;i--)
    {
        ll d=0;
        for(int j=i;j<=1000000;j+=i) d+=cnt[j];
        if(d>=2)
        {
            cout<<i;
            return 0;
        }
    }
}