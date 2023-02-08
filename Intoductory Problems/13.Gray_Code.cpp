/*
A Gray code is a list of all 2n bit strings of length n, where any two successive strings differ in exactly one bit (i.e., their Hamming distance is one).

Your task is to create a Gray code for a given length n.

Input

The only input line has an integer n.

Output

Print 2n lines that describe the Gray code. You can print any valid solution.

Constraints

    1≤n≤16


Example

Input:
2

Output:
00
01
11
10*/

//https://cp-algorithms.com/algebra/gray-code.html

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
    
    int n; cin>>n;
    int a[1<<n + 1] = {0};
    for (int i = 0; i < n; i++)
    	cout<<0;
    cout<<endl;
    a[0] = 1;
    int x = 0;
    for (int i = 1; i < 1<<n; i++) {
    	for (int j = 0; j < n; j++) {
    		int y = x^(1<<j);
    		if (!a[y]) {
    			x = y;
    			a[y] = 1;
				string s;
				while (y) {
					if (y&1) s += '1';
					else s += '0';
					y >>= 1;
				}
				reverse(s.begin(), s.end());
				for (int i = 0; i < n - s.size(); i++)
					cout<<0;
				cout<<s<<endl;
				break;
    		}
    	}
    }
}