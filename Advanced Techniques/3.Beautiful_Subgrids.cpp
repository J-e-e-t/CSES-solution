/*You are given an n×n grid whose each square is either black or white. A subgrid is called beautiful if its height and width is at least two and all of its corners are black. How many beautiful subgrids are there within the given grid?

Input

The first input line has an integer n: the size of the grid.

Then there are n lines describing the grid: 1 means that a square is black and 0 means it is white.

Output

Print the number of beautiful subgrids.

Constraints

    1≤n≤3000


Example

Input:
5
00010
11111
00110
11001
00010

Output:
4
*/

#pragma GCC target("popcnt")
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n; cin >> n;
    vector<bitset<3000>> v(n);
    for (auto &i: v)
        cin >> i;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int cnt = (v[i]&v[j]).count();
            ans += cnt * (cnt - 1) / 2;
        }
    }
    cout << ans;
}