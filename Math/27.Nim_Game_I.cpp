/*
There are n heaps of sticks and two players who move alternately. On each move, a player chooses a non-empty heap and removes any number of sticks. The player who removes the last stick wins the game.

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
3 5 6

Output:
first
first
second
*/
/*
This is a straight nim game questions where the second player wins when the xor of the elements of array is 0, and otherwise first player wins.
For more info regarding nim- https://en.wikipedia.org/wiki/Nim
*/

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
            xr^=x[i];
        }
        if(xr!=0) cout<<"first";
        else cout<<"second";
        cout<<"\n";
    }
}