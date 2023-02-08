/*
A Prüfer code of a tree of n nodes is a sequence of n−2 integers that uniquely specifies the structure of the tree.

The code is constructed as follows: As long as there are at least three nodes left, find a leaf with the smallest label, add the label of its only neighbor to the code, and remove the leaf from the tree.

Given a Prüfer code of a tree, your task is to construct the original tree.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

The second line contains n−2 integers: the Prüfer code.

Output

Print n−1 lines describing the edges of the tree. Each line has to contain two integers a and b: there is an edge between nodes a and b. You can print the edges in any order.

Constraints

    3≤n≤2⋅105


1≤a,b≤n


Example

Input:
5
2 2 4

Output:
1 2
2 3
2 4
4 5
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
    vector<int> v(n-2);
    set<int> s;
    for (int i = 1; i <= n; i++)
        s.insert(i);
    int a[n+1] = {0};
    for (auto &i: v) {
        cin>>i;
        a[i]++;
        if (s.count(i))
            s.erase(i);
    }
    for (int i = 0; i < n-2; i++) {
        int x = *s.begin();
        s.erase(x);
        cout<<x<<' '<<v[i]<<endl;
        a[v[i]]--;
        if (a[v[i]] == 0) s.insert(v[i]);
    }
    cout<<*s.begin()<<' '<<*s.rbegin();
}

