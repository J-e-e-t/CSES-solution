/*
     Time limit: 1.00 s Memory limit: 512 MB 

There are n cities in Byteland but no roads between them. However, each day, a new road will be built. There will be a total of m roads.

Your task is to process q queries of the form: "after how many days can we travel from city a to city b for the first time?"

Input

The first input line has three integers n, m and q: the number of cities, roads and queries. The cities are numbered 1,2,…,n.

After this, there are m lines that describe the roads in the order they are built. Each line has two integers a and b: there will be a road between cities a and b.

Finally, there are q lines that describe the queries. Each line has two integers a and b: we want to travel from city a to city b.

Output

For each query, print the number of days, or −1 if it is never possible.

Constraints

    1≤n,m,q≤2⋅105


1≤a,b≤n


Example

Input:
5 4 3
1 2
2 3
1 3
2 5
1 3
3 4
3 5

Output:
2
-1
4
*/

#include<bits/stdc++.h>
using namespace std;

// #define int long long
#define endl '\n'
#define F first
#define S second

const int mxN = 2e5+5;
int par[mxN], len[mxN];

void init() {
    for (int i = 0; i < mxN; i++)
        par[i] = i, len[i] = 1;
}

int find(int x) {
    if (par[x] == x)
        return x;
    return par[x] = find(par[x]);
}

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (len[x] < len[y])
            swap(x, y);
        par[y] = x;
        len[x] += len[y];
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n, m, t; cin >> n >> m >> t;
    vector<pair<int, int>> edges(m);
    for (auto &[i, j]: edges)
        cin >> i >> j;
    vector<pair<int, int>> v(t);
    for (auto &[i, j]: v)
        cin >> i >> j;

    vector<pair<int, int>> range(t);
    vector<int> ans(t, -1);
    for (int i = 0; i < t; i++) {
        range[i] = {0, m};
    }
    
    while (1) {
        init();
        vector<pair<int, int>> mid;
        for (int i = 0; i < t; i++) if (range[i].F <= range[i].S) {
            int m = (range[i].F + range[i].S) / 2;
            mid.push_back({m, i});
        }
        if (mid.size() == 0)
            break;

        sort(mid.begin(), mid.end());
        int j = 0;
        for (int i = 0; i <= m; i++) {
            if (i) join(edges[i-1].F, edges[i-1].S);
            while (j < mid.size() && mid[j].F == i) {
                int k = mid[j].S;
                if (find(v[k].F) == find(v[k].S)) {
                    ans[k] = i;
                    range[k] = {range[k].F, i-1};
                }
                else {
                    range[k] = {i+1, range[k].S};                    
                }
                j++;
            }
        }
    }
    for (int i = 0; i < t; i++)
        cout << ans[i] << endl;
}