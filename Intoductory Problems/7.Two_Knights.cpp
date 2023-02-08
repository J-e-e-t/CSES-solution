/*
Two Knights

Your task is to count for k=1,2,…,n the number of ways two knights can be placed on a k×k chessboard so that they do not attack each other.

Input

The only input line contains an integer n.

Output

Print n integers: the results.

Constraints

    1≤n≤10000


Example

Input:
8

Output:
0
6
28
96
252
550
1056
1848


*/

#include "bits/stdc++.h"
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
int main()
{
	int n;
	cin>>n;
 
	for(int i=1;i<=n;i++){
		long long sq=i*i;
 
		long long ans= (sq*(sq-1)/2)-(4*(i-1)*(i-2));
		cout<<ans<<"\n";
	}
}