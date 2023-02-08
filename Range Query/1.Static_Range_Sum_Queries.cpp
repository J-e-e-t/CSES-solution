/*
Given an array of n integers, your task is to process q queries of the form: what is the sum of values in range [a,b]?

Input

The first input line has two integers n and q: the number of values and queries.

The second line has n integers x1,x2,…,xn: the array values.

Finally, there are q lines describing the queries. Each line has two integers a and b: what is the sum of values in range [a,b]?

Output

Print the result of each query.

Constraints

    1≤n,q≤2⋅105


1≤xi≤109

1≤a≤b≤n


Example

Input:
8 4
3 2 4 5 1 1 5 3
2 4
5 6
1 8
3 3

Output:
11
2
24
4

*/


#include <bits/stdc++.h>
using namespace std;
 
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
vector<long long> sieve(long long n)
{
    vector<long long> prime;
    vector<bool> qq(n + 1, true);
    qq[0] = false;
    qq[1] = false;
 
    for (long long i = 2; i * i <= n; ++i)
    {
        if (qq[i] == true)
        {
            for (long long j = i * i; j <= n; j += i)
            {
                qq[j] = false;
            }
        }
    }
    for (long long x = 0; x < qq.size(); x++)
    {
        if (qq[x] == true)
        {
            prime.push_back(x);
        }
    }
    return prime;
}
 
int main()
{
   int n,q,x;
   cin>>n>>q;
 
   long long arr[n+1];
   arr[0]=0;
 
   for(int i=1;i<n+1;i++)
   {
       cin>>x;
       arr[i]=arr[i-1]+x;
   }
   while(q--){
       long long a,b;
       cin>>a>>b;
       long long ans=arr[b]-arr[a-1];
       cout<<ans<<"\n";
   }
}