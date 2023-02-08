/*
Your task is to calculate the area of a given polygon.

The polygon consists of n vertices (x1,y1),(x2,y2),…,(xn,yn). The vertices (xi,yi) and (xi+1,yi+1) are adjacent for i=1,2,…,n−1, and the vertices (x1,y1) and (xn,yn) are also adjacent.

Input

The first input line has an integer n: the number of vertices.

After this, there are n lines that describe the vertices. The ith such line has two integers xi and yi.

You may assume that the polygon is simple, i.e., it does not intersect itself.

Output

Print one integer: 2a where the area of the polygon is a (this ensures that the result is an integer).

Constraints

    3≤n≤1000


−109≤xi,yi≤109


Example

Input:
4
1 1
4 2
3 5
1 4

Output:
16*/


#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 1001;

int N;
ll x[maxN], y[maxN], ans;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%lld %lld", &x[i], &y[i]);
    x[N] = x[0]; y[N] = y[0];

    for(int i = 0; i < N; i++){
        ans += x[i] * y[i+1];
        ans -= y[i] * x[i+1];
    }
    printf("%lld\n", abs(ans));
}