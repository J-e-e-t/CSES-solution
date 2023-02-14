/*
Given n integers, your task is to report for each integer the number of its divisors.

For example, if x=18, the correct answer is 6 because its divisors are 1,2,3,6,9,18.

Input

The first input line has an integer n: the number of integers.

After this, there are n lines, each containing an integer x.

Output

For each integer, print the number of its divisors.

Constraints

    1≤n≤1e5


1≤x≤1e6


Example

Input:
3
16
17
18

Output:
5
2
6*/

/*
For each number i from 1 to 1000000, we increase the count of divisor of multiple of i. And then answer the queries in O(1). Time complexity is O(nlogn).
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll d[1000005]={};
    for(int i=1;i<1000005;i++)
    {
        for(int j=i;j<1000005;j+=i)
        {
            d[j]++;
        }
    }
    ll n,x;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        cout<<d[x]<<"\n";
    }
}