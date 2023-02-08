/*

There is a staircase consisting of n stairs, numbered 1,2,…,n. Initially, each stair has some number of balls.

There are two players who move alternately. On each move, a player chooses a stair k where k≠1 and it has at least one ball. Then, the player moves any number of balls from stair k to stair k−1. The player who moves last wins the game.

Your task is to find out who wins the game when both players play optimally.

Note that if there are no possible moves at all, the second player wins.

Input

The first input line has an integer t: the number of tests. After this, t test cases are described:

The first line contains an integer n: the number of stairs.

The next line has n integers p1,p2,…,pn: the initial number of balls on each stair.

Output

For each test, print "first" if the first player wins the game and "second" if the second player wins the game.

Constraints

    1≤t≤2⋅105


1≤n≤2⋅105

0≤pi≤109

the sum of all n
is at most 2⋅105


Example

Input:
3
3
0 2 1
4
1 1 1 1
2
5 3

Output:
first
second
first*/
/*
We consider elements at even position and proceed as Nim. I don’t have a proof as to why it works. There is some intuition- to empty a pile a position k , we will have to empty it all the way to position 1, which means there are (k-1) copies of that pile which we have to empty.
So if  k is odd, xor of k  even number of times is  , so the odd positions don't create an effect, and hence we consider the even positions only.
If some one has a formal proof of this, please mention it in the comments. */


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
        ll a[n];
        ll xr=0;
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
            if(i%2)
            {
                xr^=a[i];
            }
        }
        if(xr) cout<<"first";
        else cout<<"second";
        cout<<"\n";
    }
}