/*
Given a set of n points in the two-dimensional plane, your task is to determine the convex hull of the points.

Input

The first input line has an integer n: the number of points.

After this, there are n lines that describe the points. Each line has two integers x and y: the coordinates of a point.

You may assume that each point is distinct, and the area of the hull is positive.

Output

First print an integer k: the number of points in the convex hull.

After this, print k lines that describe the points. You can print the points in any order. Print all points that lie on the convex hull.

Constraints

    3≤n≤2⋅105


−109≤x,y≤109


Example

Input:
6
2 1
2 5
3 3
4 3
4 4
6 3

Output:
4
2 1
2 5
4 4
6 3*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define P complex<int>
#define X real()
#define Y imag()

int cross(P &a, P &b, P &c) {
    P u = c - b;
    P v = a - b;
    int cp = (conj(u) * v).Y;
    return (cp > 0) - (cp < 0);
}

vector<P> hull(vector<P> &v) {
    vector<P> ans = {v[0]};
    for (int i = 1; i < v.size(); i++) {
        while (ans.size() > 1) {
            P b = ans.back();
            ans.pop_back();
            P a = ans.back();
            P c = v[i];
            if (cross(a, b, c) != 1) {
                ans.push_back(b);
                break;
            }
        }
        ans.push_back(v[i]);
    }
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n; cin >> n;
    vector<P> v(n);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {x, y};
    }
    sort(v.begin(), v.end(), 
         [] (const P &a, const P &b) {
                return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
        });
    vector<P> v1 = hull(v);

    sort(v.begin(), v.end(),
         [] (const P &a, const P &b) {
                return (a.X == b.X) ? (a.Y > b.Y) : (a.X > b.X);
        });
    vector<P> v2 = hull(v);
    for (int i = 1; i < v2.size(); i++) {
        if (v2[i] == v1[0]) break;
        v1.push_back(v2[i]);
    }
    cout << v1.size() << endl;
    for (auto i: v1)
        cout << i.X << " " << i.Y << endl;
}
