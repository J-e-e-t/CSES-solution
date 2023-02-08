
/*
There are n heaps of sticks and two players who move alternately. On each move, a player chooses a non-empty heap and removes 1, 2, or 3 sticks. The player who removes the last stick wins the game.

Your task is to find out who wins if both players play optimally.

Input

The first input line contains an integer t: the number of tests. After this, t test cases are described:

The first line contains an integer n: the number of heaps.

The next line has n integers x1,x2,…,xn: the number of sticks in each heap.

Output

For each test case, print "first" if the first player wins the game and "second" if the second player wins the game.

Constraints

    1≤t≤2⋅105


1≤n≤2⋅105

1≤xi≤109

the sum of all n
is at most 2⋅105


Example

Input:
3
4
5 7 2 5
2
4 1
3
4 4 4

Output:
first
first
second

*/
/*
It’s a variation of nim game called the subtraction game where an upper bound of stones that can be removed, let say k  be given. All we have to do is to consider the pile mod (k+1), and then follow the usual nim.
For more info- https://en.wikipedia.org/wiki/Nim#The_subtraction_game*/

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
    ll t,n;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        cin>>n;
        ll x[n];
        ll xr=0;
        for(int i=0;i<n;i++)
        {
            cin>>x[i];
            x[i]%=4;
            xr^=x[i];
        }
        if(xr!=0) cout<<"first";
        else cout<<"second";
        cout<<"\n";
    }
}