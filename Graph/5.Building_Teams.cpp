/*There are n pupils in Uolevi's class, and m friendships between them. Your task is to divide the pupils into two teams in such a way that no two pupils in a team are friends. You can freely choose the sizes of the teams.

Input

The first input line has two integers n and m: the number of pupils and friendships. The pupils are numbered 1,2,…,n.

Then, there are m lines describing the friendships. Each line has two integers a and b: pupils a and b are friends.

Every friendship is between two different pupils. You can assume that there is at most one friendship between any two pupils.

Output

Print an example of how to build the teams. For each pupil, print "1" or "2" depending on to which team the pupil will be assigned. You can print any valid team.

If there are no solutions, print "IMPOSSIBLE".

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
5 3
1 2
1 3
4 5

Output:
1 2 2 1 2
*/

#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e5+1;

int N, M, a, b;
bool possible, vis[maxN], team[maxN];
vector<int> G[maxN];

void dfs(int u, int p = 0){
    for(int v : G[u]){
        if(v != p){
            if(!vis[v]){
                team[v] = !team[u];
                vis[v] = true;
                dfs(v, u);
            } else
                if(team[v] == team[u])
                    possible = false;
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    possible = true;
    for(int i = 1; i <= N; i++){
        if(!vis[i]){
            vis[i] = true;
            dfs(i);
        }
    }

    if(!possible)
        printf("IMPOSSIBLE\n");
    else
        for(int i = 1; i <= N; i++)
            printf("%d%c", (team[i] ? 1 : 2), (" \n")[i==N]);
}