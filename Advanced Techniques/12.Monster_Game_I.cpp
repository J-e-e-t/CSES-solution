/*
You are playing a game that consists of n levels. Each level has a monster. On levels 1,2,…,n−1, you can either kill or escape the monster. However, on level n you must kill the final monster to win the game.

Killing a monster takes sf time where s is the monster's strength and f is your skill factor (lower skill factor is better). After killing a monster, you get a new skill factor. What is the minimum total time in which you can win the game?

Input

The first input line has two integers n and x: the number of levels and your initial skill factor.

The second line has n integers s1,s2,…,sn: each monster's strength.

The third line has n integers f1,f2,…,fn: your new skill factor after killing a monster.

Output

Print one integer: the minimum total time to win the game.

Constraints

    1≤n≤2⋅105


1≤x≤106

1≤s1≤s2≤⋯≤sn≤106

x≥f1≥f2≥⋯≥fn≥1


Example

Input:
5 100
20 30 30 50 90
90 60 20 20 10

Output:
4800

Explanation: The best way to play is to kill the third and fifth monster. 
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define F first
#define S second

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n, k; cin >> n >> k;
    vector<pair<int, int>> S = {{k, 0}};
    vector<int> v = {1};
    int s[n], f[n];
    for (auto &i: s)
        cin >> i;
    for (auto &i: f)
        cin >> i;
    int c = 0;
    for (int i = 0; i < n; i++) {
        int x = s[i];
        int it = upper_bound(v.begin(), v.end(), x) - v.begin() - 1;
        int m = f[i];
        c = x*S[it].F + S[it].S;
        if (S.back().F == m) continue; // if same slope then always bad line
        while (S.size() >= 2) {
            auto y2 = S[S.size() - 1];
            auto y3 = S[S.size() - 2];
            if ((y2.S - c)*(m - y3.F) < (y3.S - c)*(m - y2.F)) {
                S.pop_back();
                v.pop_back();
            }
            else break;
        }
        int x1 = ceil((S.back().S - c)*1.0/(m - S.back().F));
        v.push_back(x1);
        S.push_back({m, c});
    }
    cout << c;
}