/*
     Time limit: 1.00 s Memory limit: 512 MB 

The Hamming distance between two strings a and b of equal length is the number of positions where the strings differ.

You are given n bit strings, each of length k and your task is to calculate the minimum Hamming distance between two strings.

Input

The first input line has two integers n and k: the number of bit strings and their length.

Then there are n lines each consisting of one bit string of length k.

Output

Print the minimum Hamming distance between two strings.

Constraints

    2≤n≤2⋅104


1≤k≤30


Example

Input:
5 6
110111
001000
100001
101000
101110

Output:
1

Explanation: The strings 101000 and 001000 differ only at the first position
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
    
    int n,k; cin>>n>>k;
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
    	string s; cin>>s;
    	reverse(s.begin(), s.end());
    	for (int j = 0; j < s.size(); j++) {
    		v[i] += (s[j] == '1')*(1<<j);
    	}
    }
    int ans = 32;
    for (int i = 0; i < n; i++) {
    	for (int j = i+1; j < n; j++) {
    		ans = min(ans, (int) __builtin_popcount(v[i]^v[j]));
    	}
    }
    cout<<ans;
}