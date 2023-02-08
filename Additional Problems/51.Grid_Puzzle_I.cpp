/*
There is an n×n grid, and your task is to choose from each row and column some number of squares. How can you do that?

Input

The first input line has an integer n: the size of the grid. The rows and columns are numbered 1,2,…,n.

The next line has n integers a1,a2,…,an: You must choose exactly ai squares from the ith row.

The las line has n integers b1,b2,…,bn: You must choose exactly bj squares from the jth column.

Output

Print n lines describing which squares you choose (X means that you choose a square, . means that you don't choose it). You can print any valid solution.

If it is not possible to satisfy the conditions print only −1.

Constraints

    1≤n≤50


0≤ai≤n

0≤bj≤n


Example

Input:
5
0 1 3 2 0
1 2 2 0 1

Output:
.....
..X..
.XX.X
XX...
.....
*/
#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int maxN = 105, maxM = 2605;
const int INF = 0x3f3f3f3f;

int N, rowTot, colTot, edgeID, p[maxN], cap[maxN][maxN];
bool vis[maxM];
vector<int> path, F[maxN];
vector<pii> G[maxN];

int bfs(int s = 0, int t = 2*N+1){
    fill(p, p+2*N+2, -1);
    p[s] = -2;

    queue<pii> Q;
    Q.push({s, INF});
    while(!Q.empty()){
        int u = Q.front().first;
        int f = Q.front().second;
        Q.pop();

        for(int v : F[u]){
            if(p[v] == -1 && cap[u][v]){
                p[v] = u;
                int aug = min(f, cap[u][v]);
                if(v == t)  return aug;
                Q.push({v, aug});
            }
        }
    }

    return 0;
}

void dfs(int u = 0){
    path.push_back(u);
    if(u == N)  return;
    for(pii e : G[u]){
        int v = e.first;
        int id = e.second;
        if(cap[u][v] == 0 && !vis[id]){
            vis[id] = true;
            dfs(v);
            return;
        }
    }
}

int maxflow(int s = 0, int t = 2*N+1){
    int flow = 0, aug = 0;
    while(aug = bfs()){
        flow += aug;
        int u = t;
        while(u != s){
            int v = p[u];
            cap[v][u] -= aug;
            cap[u][v] += aug;
            u = v;
        }
    }
    return flow;
}

int main(){
    scanf("%d", &N);
    for(int i = 1, c; i <= N; i++){
        scanf("%d", &c);
        G[0].push_back({i, ++edgeID});
        F[0].push_back(i);
        F[i].push_back(0);
        cap[0][i] += c;
        rowTot += c;
    }
    for(int i = N+1, c; i <= 2*N; i++){
        scanf("%d", &c);
        G[i].push_back({2*N+1, ++edgeID});
        F[i].push_back(2*N+1);
        F[2*N+1].push_back(i);
        cap[i][2*N+1] += c;
        colTot += c;
    }
    for(int i = 1; i <= N; i++){
        for(int j = N+1; j <= 2*N; j++){
            G[i].push_back({j, ++edgeID});
            F[i].push_back(j);
            F[j].push_back(i);
            cap[i][j]++;
        }
    }

    int K = maxflow();
    if(rowTot != colTot || K != rowTot){
        printf("-1\n");
        return 0;
    }

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++)
            printf("%c", (cap[i][j+N] ? '.' : 'X'));
        printf("\n");
    }
}