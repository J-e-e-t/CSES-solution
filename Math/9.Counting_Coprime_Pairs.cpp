
/*
Given a list of n positive integers, your task is to count the number of pairs of integers that are coprime (i.e., their greatest common divisor is one).

Input

The first input line has an integer n: the number of elements.

The next line has n integers x1,x2,…,xn: the contents of the list.

Output

Print one integer: the answer for the task.

Constraints

    1≤n≤105


1≤xi≤106


Example

Input:
8
5 4 20 1 16 17 5 15

Output:
19
*/

/*
We will be using Mobius function m(k) for it. You can read about it here — https://en.wikipedia.org/wiki/M%C3%B6bius_function.

The answer to the problem is summation of m(k)*(d[k]c2) for all k = 1,,, max(x[i])       . Here d(k) is the number of integers in given sequence that are divisible by k.

We see that this result comes from the Inclusion-Exclusion principle. The term in the summation corresponds to choosing two numbers which are multiples of k, and m(k)  decides whether we add it or not. Note that in inclusion-exclusion, we don’t consider k which aren’t square free, as it doesn’t add any effect to our answer.
Time complexity is O(10^6 log(10^6)). Check the code below for implementation of Mobius function.
A similar problem for reference — https://discuss.codechef.com/t/coprime3-editorial/6051

*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long MOD = 1e9 + 7;
using vll = vector<ll>;

ll lpf[1000001],mobius[1000001];

void least_prime_factor()
{
    for(int i=2;i<1000001;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<1000001;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<1000001;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin>>n;
    ll x[n],cnt[1000001]={};
    for(int i=0;i<n;i++)
    {
        cin>>x[i];
        cnt[x[i]]++;
    }
    least_prime_factor();
    Mobius();
    ll ans=0;
    for(int i=1;i<1000001;i++)
    {
        if(mobius[i]==0) continue;
        ll d=0;
        for(int j=i;j<1000001;j+=i)
        {
            d+=cnt[j];
        }
        ans+=(d*(d-1))/2*mobius[i];
    }
    cout<<ans;
}