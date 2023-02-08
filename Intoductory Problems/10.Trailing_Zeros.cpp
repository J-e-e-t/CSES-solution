/*
Your task is to calculate the number of trailing zeros in the factorial n!.

For example, 20!=2432902008176640000 and it has 4 trailing zeros.

Input

The only input line has an integer n.

Output

Print the number of trailing zeros in n!.

Constraints

    1≤n≤109


Example

Input:
20

Output:
4*/

#include <bits/stdc++.h>
using namespace std;
 
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
int main()
{
    long long n;
    cin>>n;
 
    long cnt=0;
 
    long i=5;
    while(n/i>=1)
    {
        cnt+= n/i;
        i*=5;
    }
    cout<<cnt;
}
