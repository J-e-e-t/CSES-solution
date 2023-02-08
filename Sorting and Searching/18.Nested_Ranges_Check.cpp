/*
Given n ranges, your task is to determine for each range if it contains some other range and if some other range contains it.

Range [a,b] contains range [c,d] if a≤c and d≤b.

Input

The first input line has an integer n: the number of ranges.

After this, there are n lines that describe the ranges. Each line has two integers x and y: the range is [x,y].

You may assume that no range appears more than once in the input.

Output

First print a line that describes for each range (in the input order) if it contains some other range (1) or not (0).

Then print a line that describes for each range (in the input order) if some other range contains it (1) or not (0).

Constraints

    1≤n≤2⋅105


1≤x<y≤109


Example

Input:
4
1 6
2 4
4 8
3 6

Output:
1 0 0 0
0 1 0 1
*/
#include <bits/stdc++.h>

using namespace std;
typedef array<int,3> triple;
const int maxN = 2e5+1;
const int SIZE = 2*maxN;

int N, ans[2][maxN], ds[SIZE];
triple ranges[maxN];
set<int> unique_vals;
map<int,int> mp;

void update(int idx, int val){
    for(int i = idx; i < SIZE; i += -i&i)   ds[i] += val;
}

int query(int idx){
    int cnt = 0;
    for(int i = idx; i > 0; i -= -i&i)
        cnt += ds[i];
    return cnt;
}

int main(){
    scanf("%d", &N);
    for(int i = 0, x, y; i < N; i++){
        scanf("%d %d", &x, &y);
        ranges[i] = {x, y, i};
        unique_vals.insert(x);
        unique_vals.insert(y);
    }
    sort(ranges, ranges+N, [](triple A, triple B){
        return (A[0] == B[0] ? A[1] > B[1] : A[0] < B[0]);
    });

    int val_id = 1;
    for(int x : unique_vals)
        mp[x] = val_id++;

    for(int i = N-1; i >= 0; i--){
        int y = mp[ranges[i][1]];
        int id = ranges[i][2];

        ans[0][id] = query(y);
        update(y, 1);
    }

    fill(ds, ds+SIZE, 0);
    for(int i = 0; i < N; i++){
        int y = mp[ranges[i][1]];
        int id = ranges[i][2];

        ans[1][id] = i-query(y-1);
        update(y, 1);
    }

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < N; j++)
            printf("%d%c", (ans[i][j] ? 1 : 0), (" \n")[j==N-1]);
}