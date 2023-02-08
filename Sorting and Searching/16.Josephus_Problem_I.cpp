
/*
Consider a game where there are n children (numbered 1,2,…,n) in a circle. During the game, every other child is removed from the circle until there are no children left. In which order will the children be removed?

Input

The only input line has an integer n.

Output

Print n integers: the removal order.

Constraints

    1≤n≤2⋅105


Example

Input:
7

Output:
2 4 6 1 5 3 7
*/
/*
Problem Name: Josephus Problem I
Problem Link: https://cses.fi/problemset/task/2162
Author: Sachin Srivastava (mrsac7)
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
    
    int n; cin>>n;
    int a = 1, b = 0;
    while(n > 0) {
    	for (int i = 2; i <= n; i+=2) {
    		cout<<a*i + b<<' ';
    	}
    	if (n&1) cout<<a + b<<' ', b += a;
    	else b -= a;
    	a <<= 1;
    	n >>= 1;
    }
}