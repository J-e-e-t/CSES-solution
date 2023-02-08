/*
There are n heaps of coins and two players who move alternately. On each move, a player selects some of the nonempty heaps and removes one coin from each heap. The player who removes the last coin wins the game.

Your task is to find out who wins if both players play optimally.

Input

The first input line contains an integer t: the number of tests. After this, t test cases are described:

The first line contains an integer n: the number of heaps.

The next line has n integers x1,x2,…,xn: the number of coins in each heap.

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
3
1 2 3
2
2 2
4
5 5 4 5

Output:
first
second
first

*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int t; cin>>t;
    while (t--) {
        int n; cin>>n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x; cin>>x;
            if (x&1) ans = 1;
        }
        cout<<(ans ? "first" : "second")<<endl;
    }   
}