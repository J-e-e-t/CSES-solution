/*
You are given an array that contains each number between 1…n exactly once. Your task is to collect the numbers from 1 to n in increasing order.

On each round, you go through the array from left to right and collect as many numbers as possible.

Given m operations that swap two numbers in the array, your task is to report the number of rounds after each operation.

Input

The first line has two integers n and m: the array size and the number of operations.

The next line has n integers x1,x2,…,xn: the numbers in the array.

Finally, there are m lines that describe the operations. Each line has two integers a and b: the numbers at positions a and b are swapped.

Output

Print m integers: the number of rounds after each swap.

Constraints

    1≤n,m≤2⋅105


1≤a,b≤n


Example

Input:
5 3
4 2 1 5 3
2 3
1 5
2 3

Output:
2
3
4
*/

/*
Problem Name: Collecting Numbers II
Problem Link: https://cses.fi/problemset/task/2217
Author: Sachin Srivastava (mrsac7)
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
    
    int n,m; cin>>n>>m;
    int l = 1;
    int ind[n+2] = {0}, a[n+1] = {0};
    ind[n+1] = n+1;
    for (int i = 1; i <= n; i++) {
		int x; cin>>x;
		ind[x] = i;
		a[i] = x;
    }
    int c = 1;
    for (int i = 1; i <= n; i++) {
		if (l > ind[i]) 
		c++;
		l = ind[i];
    }
    while(m--) {
		int x,y; cin>>x>>y;
		int r = a[x], s = a[y];
		swap(a[x], a[y]);
		if (ind[r-1] <= ind[r] && ind[r-1] > y) c++;
		if (ind[r-1] > ind[r] && ind[r-1] <= y) c--;
		if (ind[r] <= ind[r+1] && y > ind[r+1]) c++;
		if (ind[r] > ind[r+1] && y <= ind[r+1]) c--;		
		ind[r] = y;
		if (ind[s-1] <= ind[s] && ind[s-1] > x) c++;
		if (ind[s-1] > ind[s] && ind[s-1] <= x) c--;
		if (ind[s] <= ind[s+1] && x > ind[s+1]) c++;
		if (ind[s] > ind[s+1] && x <= ind[s+1]) c--;	
		ind[s] = x;
		cout<<c<<endl;
    }
}