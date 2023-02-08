/*
Given n horizontal and vertical line segments, your task is to calculate the number of their intersection points.

You can assume that no parallel line segments intersect, and no endpoint of a line segment is an intersection point.

Input

The first input line has an integer n: the number of line segments.

Then there are n lines describing the line segments. Each line has four integers: x1, y1, x2 and y2: a line segment begins at point (x1,y1) and ends at point (x2,y2).

Output

Print the number of intersection points.

Constraints

    1≤n≤105


−106≤x1≤x2≤106

−106≤y1≤y2≤106

(x1,y1)≠(x2,y2)


Example

Input:
3
2 3 7 3
3 1 3 5
6 2 6 6

Output:
2
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 1e5+1;
const int maxX = 1e6+5;
const int SIZE = 2*maxX;

struct Operation {
    int type, y, a, b;
};

int N, ds[SIZE];
vector<Operation> ops;

void update(int idx, int val){
    for(int i = idx; i < SIZE; i += -i&i)
        ds[i] += val;
}

int query(int idx){
    int sum = 0;
    for(int i = idx; i > 0; i -= -i&i)
        sum += ds[i];
    return sum;
}

int main(){
    scanf("%d", &N);
    for(int i = 0, a, b, c, d; i < N; i++){
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if(a == c){
            // Vertical
            ops.push_back({2, b, a+maxX, -1});
            ops.push_back({3, d, a+maxX, -1});
        } else {
            // Horizontal
            ops.push_back({1, b, a+maxX, c+maxX});
        }
    }
    sort(ops.begin(), ops.end(), [](Operation A, Operation B){
        return A.y < B.y;
    });

    ll ans = 0;
    for(Operation O : ops){
        if(O.type == 1)         ans += query(O.b) - query(O.a-1);
        else if(O.type == 2)    update(O.a, 1);
        else if(O.type == 3)    update(O.a, -1);
    }
    printf("%lld\n", ans);
}