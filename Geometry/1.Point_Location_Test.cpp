/*
There is a line that goes through the points p1=(x1,y1) and p2=(x2,y2). There is also a point p3=(x3,y3).

Your task is to determine whether p3 is located on the left or right side of the line or if it touches the line when we are looking from p1 to p2.

Input

The first input line has an integer t: the number of tests.

After this, there are t lines that describe the tests. Each line has six integers: x1, y1, x2, y2, x3 and y3.

Output

For each test, print "LEFT", "RIGHT" or "TOUCH".

Constraints

    1≤t≤105


−109≤x1,y1,x2,y2,x3,y3≤109

x1≠x2
or y1≠y2


Example

Input:
3
1 1 5 3 2 3
1 1 5 3 4 1
1 1 5 3 3 2

Output:
LEFT
RIGHT
TOUCH
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int t; cin>>t;
    while (t--) {
        int x1, y1, x2, y2, x3, y3;
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        //cross product
        int cp = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
        if (cp < 0) cout<<"RIGHT"<<endl;
        if (cp > 0) cout<<"LEFT"<<endl;
        if (cp == 0) cout<<"TOUCH"<<endl;        
    }
}