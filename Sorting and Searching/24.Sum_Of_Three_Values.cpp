/*
You are given an array of n integers, and your task is to find three values (at distinct positions) whose sum is x.

Input

The first input line has two integers n and x: the array size and the target sum.

The second line has n integers a1,a2,…,an: the array values.

Output

Print three integers: the positions of the values. If there are several solutions, you may print any of them. If there are no solutions, print IMPOSSIBLE.

Constraints

    1≤n≤5000


1≤x,ai≤109


Example

Input:
4 8
2 7 5 1

Output:
1 3 4*/

#include<bits/stdc++.h>
using namespace std;
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,x; cin >> n >> x;
	vector<pair<int, int>> arr;
	for(int i = 1; i <= n; i++){
		int a; cin >> a;
		pair<int, int> p; p.first = a; p.second = i;
		// first in pair represents value, second represents index
		arr.push_back(p);
	}
	sort(begin(arr), end(arr));
	for(int i = 0; i < n; i++){
		int l, r; l = 0; r = n-1;
		while(l != r){
			int target; target = x - arr.at(i).first;
			if(l != i && r != i && arr.at(l).first + arr.at(r).first == target){
				cout << arr.at(i).second << " " << arr.at(l).second
					 << " " << arr.at(r).second << endl;
				return 0;
			}
			if(arr.at(l).first + arr.at(r).first < target){
				l++;
			}
			else{
				r--;
			}
		}
	}
	cout << "IMPOSSIBLE" << endl;
}