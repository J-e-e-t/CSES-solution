
/*
Given an array of n integers, your task is to calculate the number of subarrays that have at most k distinct values.

Input

The first input line has two integers n and k.

The next line has n integers x1,x2,…,xn: the contents of the array.

Output

Print one integer: the number of subarrays.

Constraints

    1≤k≤n≤2⋅105


1≤xi≤109


Example

Input:
5 2
1 2 3 1 1

Output:
10*/

/*
Problem Name: Subarray Distinct Values
Problem Link: https://cses.fi/problemset/task/2428
Author: Sachin Srivastava (mrsac7)
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

map<int,int> cnt;

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int k, n; cin>>n>>k;
    int a[n];
    for (int i = 0; i < n; i++) 
        cin>>a[i];
    int l = 0, r = 0, c = 0, ans = 0;
    while(l < n) {
        while(r < n && c + (cnt[a[r]] == 0) <= k) {
            cnt[a[r]]++; 
            c += (cnt[a[r]] == 1);
            r++; 
        }
        ans += r-l;
        c -= (cnt[a[l]] == 1);
        cnt[a[l]]--, l++;
    }
    cout<<ans;
}