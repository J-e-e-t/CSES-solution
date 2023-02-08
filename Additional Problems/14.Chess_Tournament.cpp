/*
There will be a chess tournament of n players. Each player has announced the number of games they want to play.

Each pair of players can play at most one game. Your task is to determine which games will be played so that everybody will be happy.

Input

The first input line has an integer n: the number of players. The players are numbered 1,2,…,n.

The next line has n integers x1,x2,…,xn: for each player, the number of games they want to play.

Output

First print an integer k: the number of games. Then, print k lines describing the games. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

Constraints

    1≤n≤105


∑ni=1xi≤2⋅105


Example

Input:
5
1 3 2 0 2

Output:
4
1 2
2 3
2 5
3 5
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> pii;

int N, K;
vector<pii> added, ans;
tree<pii, null_type, less<pii>, rb_tree_tag,
tree_order_statistics_node_update> T;

int main(){
    scanf("%d", &N);
    for(int i = 1, x; i <= N; i++){
        scanf("%d", &x);
        T.insert({x, i});
    }

    for(int i = N-1; i >= 0; i--){
        pii P = *T.find_by_order(i);
        T.erase(T.find_by_order(i));
        int degu = P.first;
        int u = P.second;

        added.clear();
        for(int j = 1; j <= degu; j++){
            if(i-j < 0 || (*T.find_by_order(i-j)).first == 0){
                printf("IMPOSSIBLE\n");
                return 0;
            }

            pii Q = *T.find_by_order(i-j);
            T.erase(T.find_by_order(i-j));
            int degv = Q.first;
            int v = Q.second;

            ans.push_back({min(u, v), max(u, v)});
            added.push_back({degv-1, v});
        }

        for(pii Q : added)
            T.insert({Q.first, Q.second});
    }

    sort(ans.begin(), ans.end());
    K = (int) ans.size();
    printf("%d\n", K);
    for(int i = 0; i < K; i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
}