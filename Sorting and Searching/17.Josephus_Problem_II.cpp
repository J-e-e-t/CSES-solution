
/*
Consider a game where there are n children (numbered 1,2,…,n) in a circle. During the game, repeatedly k children are skipped and one child is removed from the circle. In which order will the children be removed?

Input

The only input line has two integers n and k.

Output

Print n integers: the removal order.

Constraints

    1≤n≤2⋅105


0≤k≤109


Example

Input:
7 2

Output:
3 6 2 7 5 1 4


*/


//https://cp-algorithms.com/others/josephus_problem.html
/*
Problem Name: Josephus Problem II
Problem Link: https://cses.fi/problemset/task/2163
Author: Sachin Srivastava (mrsac7)
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;
#define int long long
#define endl '\n'

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    indexed_set s;
    int n,k; cin>>n>>k;
    for (int i = 1; i <= n; i++)
        s.insert(i);

    int ind = k%n;
    while(n--) {
        auto y = s.find_by_order(ind);
        cout<<*y<<' ';
        s.erase(y);
        if (n) ind = (ind%n + k)%n;
    }   
}
