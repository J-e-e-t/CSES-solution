/*
You want to complete n courses that have requirements of the form "course a has to be completed before course b".

You want to complete course 1 as soon as possible. If there are several ways to do this, you want then to complete course 2 as soon as possible, and so on.

Your task is to determine the order in which you complete the courses.

Input

The first input line has two integers n and m: the number of courses and requirements. The courses are numbered 1,2,…,n.

Then, there are m lines describing the requirements. Each line has two integers a and b: course a has to be completed before course b.

You can assume that there is at least one valid schedule.

Output

Print one line having n integers: the order in which you complete the courses.

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
4 2
2 1
2 3

Output:
2 1 3 4
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 2e5;

int N, M, a, b, idx, in[maxN], ans[maxN];
vector<int> G[maxN];
priority_queue<int> Q;

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        G[b].push_back(a);
        in[a]++;
    }

    for(int i = 1; i <= N; i++)
        if(in[i] == 0)
            Q.push(i);

    idx = N;
    while(!Q.empty()){
        int u = Q.top(); Q.pop();
        ans[idx--] = u;
        for(int v : G[u]){
            in[v]--;
            if(in[v] == 0)
                Q.push(v);
        }
    }

    for(int i = 1; i <= N; i++)
        printf("%d%c", ans[i], (" \n")[i==N]);
}
