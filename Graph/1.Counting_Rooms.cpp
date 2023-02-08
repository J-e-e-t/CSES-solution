/*
You are given a map of a building, and your task is to count the number of its rooms. The size of the map is n×m squares, and each square is either floor or wall. You can walk left, right, up, and down through the floor squares.

Input

The first input line has two integers n and m: the height and width of the map.

Then there are n lines of m characters describing the map. Each character is either . (floor) or # (wall).

Output

Print one integer: the number of rooms.

Constraints

    1≤n,m≤1000


Example

Input:
5 8
########
#..#...#
####.#.#
#..#...#
########

Output:
3*/

#include <bits/stdc++.h>

using namespace std;

char c;
int N, M, cnt;
int h[] = {1, -1, 0, 0}, v[] = {0, 0, 1, -1};
bool vis[1000][1000];

void dfs(int x, int y){
    vis[x][y] = true;
    for(int i = 0; i < 4; i++){
        int dx = x+h[i], dy = y+v[i];
        if(0 <= dx && dx < N && 0 <= dy && dy < M && !vis[dx][dy])
            dfs(dx, dy);
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            scanf(" %c", &c);
            vis[i][j] = (c == '#');
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(!vis[i][j]){
                dfs(i, j);
                cnt++;
            }
        }
    }
    printf("%d\n", cnt);
}
