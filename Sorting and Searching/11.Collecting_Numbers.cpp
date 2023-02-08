/*
You are given an array that contains each number between 1…n exactly once. Your task is to collect the numbers from 1 to n in increasing order.

On each round, you go through the array from left to right and collect as many numbers as possible. What will be the total number of rounds?

Input

The first line has an integer n: the array size.

The next line has n integers x1,x2,…,xn: the numbers in the array.

Output

Print one integer: the number of rounds.

Constraints

    1≤n≤2⋅105


Example

Input:
5
4 2 1 5 3

Output:
3*/

#include "bits/stdc++.h"
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
int main()
{
	int n,a;
	cin>>n;
 
	int arr[n+1];
 
	unordered_map<int,int> mymap;
 
	for(int i=1;i<=n;i++){
		cin>>a;
		arr[i]=a;
		mymap[a]=i+1;
	}
 
	int cnt=1;
 
	for(int i=2;i<=n;i++){
		if(mymap[i]<mymap[i-1]){
			cnt++;
		}
	}
	cout<<cnt<<"\n";
}