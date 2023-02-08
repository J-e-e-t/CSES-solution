/*
In a movie festival, n movies will be shown. You know the starting and ending time of each movie.

Your task is to process q queries of the form: if you arrive and leave the festival at specific times, what is the maximum number of movies you can watch?

You can watch two movies if the first movie ends before or exactly when the second movie starts. You can start the first movie exactly when you arrive and leave exactly when the last movie ends.

Input

The first input line has two integers n and q: the number of movies and queries.

After this, there are n lines describing the movies. Each line has two integers a and b: the starting and ending time of a movie.

Finally, there are q lines describing the queries. Each line has two integers a and b: your arrival and leaving time.

Output

Print the maximum number of movies for each query.

Constraints

    1≤n,q≤2⋅105


1≤a<b≤106


Example

Input:
4 3
2 5
6 10
4 7
9 10
5 9
2 10
7 10

Output:
0
2
1
*/
#include <bits/stdc++.h>

using namespace std;
const int logN = 17, maxT = 1e6;

int N, Q, dp[maxT+1][logN+1];
vector<int> movies[maxT+1];

int main(){
    scanf("%d %d", &N, &Q);
    for(int i = 0, a, b; i < N; i++){
        scanf("%d %d", &a, &b);
        movies[a].push_back(b);
    }

    priority_queue<int, vector<int>, greater<int>> ends;
    for(int t = maxT; t >= 0; t--){
        for(int b : movies[t])
            ends.push(b);

        dp[t][0] = ends.empty() ? maxT+1 : ends.top();
    }
    for(int k = 1; k <= logN; k++)
        for(int t = 0; t <= maxT; t++)
            dp[t][k] = dp[t][k-1] > maxT ? maxT+1 : dp[dp[t][k-1]][k-1];

    for(int q = 0, a, b; q < Q; q++){
        scanf("%d %d", &a, &b);
        int ans = 0;
        for(int k = logN; k >= 0; k--){
            if(dp[a][k] <= b){
                a = dp[a][k];
                ans += (1<<k);
            }
        }
        printf("%d\n", ans);
    }
}