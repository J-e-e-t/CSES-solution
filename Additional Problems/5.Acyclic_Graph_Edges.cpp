/*
Given an undirected graph, your task is to choose a direction for each edge so that the resulting directed graph is acyclic.

Input

The first input line has two integers n and m: the number of nodes and edges. The nodes are numbered 1,2,…,n.

After this, there are m lines describing the edges. Each line has two distinct integers a and b: there is an edge between nodes a and b.

Output

Print m lines describing the directions of the edges. Each line has two integers a and b: there is an edge from node a to node b. You can print any valid solution.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
3 3
1 2
2 3
3 1

Output:
1 2
3 2
3 1
*/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
void solve()
{
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        if (a > b)
            swap(a, b);
        cout << a << " " << b << endl;
    }
 
}
 
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
 
#ifdef _DEBUG
    freopen("input-1.txt", "r", stdin);
    //freopen("output-1.txt", "w", stdout);
#endif
 
    solve();
    //int t; cin >> t; while(t--) solve();
 
    return 0;
}
