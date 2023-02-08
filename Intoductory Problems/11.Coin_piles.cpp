/*
You have two coin piles containing a and b coins. On each move, you can either remove one coin from the left pile and two coins from the right pile, or two coins from the left pile and one coin from the right pile.

Your task is to efficiently find out if you can empty both the piles.

Input

The first input line has an integer t: the number of tests.

After this, there are t lines, each of which has two integers a and b: the numbers of coins in the piles.

Output

For each test, print "YES" if you can empty the piles and "NO" otherwise.

Constraints

    1≤t≤105


0≤a,b≤109


Example

Input:
3
2 1
2 2
3 3

Output:
YES
NO
YES*/

#include <bits/stdc++.h>
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        long long a,b;
        cin>>a>>b;
        
        if(a==0 && b==0){
            cout<<"YES \n";
            continue;
        }
 
        if((a+b)%3!=0){
            cout<<"NO \n";
            continue;
        }
        
        long long mx=max(a,b);
        long long mn=min(a,b);
 
        if(mx>2*mn){
            cout<<"NO \n";
            continue;
        }
        cout<<"YES \n";
        continue;
 
 
 
        
    }
}


