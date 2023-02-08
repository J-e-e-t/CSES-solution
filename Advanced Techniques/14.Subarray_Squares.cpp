/*
     Time limit: 1.00 s Memory limit: 512 MB 

Given an array of n elements, your task is to divide into k subarrays. The cost of each subarray is the square of the sum of the values in the subarray. What is the minimum total cost if you act optimally?

Input

The first input line has two integers n and k: the array elements and the number of subarrays. The array elements are numbered 1,2,…,n.

The second line has n integers x1,x2,…,xn: the contents of the array.

Output

Print one integer: the minimum total cost.

Constraints

    1≤k≤n≤3000


1≤xi≤105


Example

Input:
8 3
2 3 1 2 2 3 4 1

Output:
110

Explanation: An optimal solution is [2,3,1], [2,2,3], [4,1], whose cost is (2+3+1)2+(2+2+3)2+(4+1)2=110. 
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 3005;
int a[mxN], pre[mxN];
vector<int> dp_prev(mxN), dp_cur(mxN);
const int INF = 1LL<<60;

int cost(int l, int r) {
    return (pre[r] - pre[l-1]) * (pre[r] - pre[l-1]);
}

void solve(int a, int b, int x, int y) {
    if (a > b)
        return;
    int m = (a + b) / 2;
    pair<int, int> p = {INF, -1};
    for (int i = x; i <= min(m, y); i++) {
        p = min(p, {dp_prev[i] + cost(i+1, m), i});
    }
    dp_cur[m] = p.first;
    solve(a, m-1, x, p.second);
    solve(m+1, b, p.second, y);    
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i+1] = pre[i] + a[i];
    }

    for (int i = 1; i <= n; i++)
        dp_prev[i] = cost(1, i);

    for (int i = 2; i <= k; i++) {
        solve(1, n, 1, n);
        dp_prev = dp_cur;
    }
    cout << dp_prev[n];
}