/*
You are given a polygon of n vertices and a list of m points. Your task is to determine for each point if it is inside, outside or on the boundary of the polygon.

The polygon consists of n vertices (x1,y1),(x2,y2),…,(xn,yn). The vertices (xi,yi) and (xi+1,yi+1) are adjacent for i=1,2,…,n−1, and the vertices (x1,y1) and (xn,yn) are also adjacent.

Input

The first input line has two integers n and m: the number of vertices in the polygon and the number of points.

After this, there are n lines that describe the polygon. The ith such line has two integers xi and yi.

You may assume that the polygon is simple, i.e., it does not intersect itself.

Finally, there are m lines that describe the points. Each line has two integers x and y.

Output

For each point, print "INSIDE", "OUTSIDE" or "BOUNDARY".

Constraints

    3≤n,m≤1000


1≤m≤1000

−109≤xi,yi≤109

−109≤x,y≤109


Example

Input:
4 3
1 1
4 2
3 5
1 4
2 3
3 1
1 3

Output:
INSIDE
OUTSIDE
BOUNDARY
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 1001;

struct Point {
    int x, y;
    void read(){ scanf("%d %d", &x, &y); }
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; }
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; }
    ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point& b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }

    ll cross(const Point& b, const Point& c) const {
        return (b - *this) * (c - *this);
    }
};

int N, M;
Point P[maxN];

bool pointlineintersect(Point P1, Point P2, Point P3){
    if(P2.cross(P1, P3) != 0)   return false;
    return (min(P2.x, P3.x) <= P1.x && P1.x <= max(P2.x, P3.x))
        && (min(P2.y, P3.y) <= P1.y && P1.y <= max(P2.y, P3.y));
}

void pointinpolygon(){
    int cnt = 0;
    bool boundary = false;
    for(int i = 1; i <= N; i++){
        int j = (i == N ? 1 : i+1);
        if(pointlineintersect(P[0], P[i], P[j]))
            boundary = true;

        if(P[i].x <= P[0].x && P[0].x < P[j].x && P[0].cross(P[i], P[j]) < 0)       cnt++;
        else if(P[j].x <= P[0].x && P[0].x < P[i].x && P[0].cross(P[j], P[i]) < 0)  cnt++;
    }

    if(boundary)    printf("BOUNDARY\n");
    else if(cnt&1)  printf("INSIDE\n");
    else            printf("OUTSIDE\n");
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++)
        P[i].read();
    for(int i = 0; i < M; i++){
        P[0].read();
        pointinpolygon();
    }
}