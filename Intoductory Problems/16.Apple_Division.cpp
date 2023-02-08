/*
There are n apples with known weights. Your task is to divide the apples into two groups so that the difference between the weights of the groups is minimal.

Input

The first input line has an integer n: the number of apples.

The next line has n integers p1,p2,…,pn: the weight of each apple.

Output

Print one integer: the minimum difference between the weights of the groups.

Constraints

    1≤n≤20


1≤pi≤109


Example

Input:
5
3 2 7 4 1

Output:
1

Explanation: Group 1 has weights 2, 3 and 4 (total weight 9), and group 2 has weights 1 and 7 (total weight 8). 
*/


/*
Since 
$n\le 20$
, we can solve the focus problem by trying all possible divisions
of 
$n$
 apples into two sets and finding the one with the minimum difference in
weights. Here are two ways to do this.

Generating Subsets Recursively

The first method would be to write a recursive function which searches over all
possibilities.

At some index, we either add $\texttt{weight}_i$ to the first set or the second
set, storing two sums $\texttt{sum}_1$ and $\texttt{sum}_2$ with the sum of values in each set.

Then, we return the difference between the two sums once we've reached the end
of the array

*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
ll weight[20];

ll solve(int i, ll sum1, ll sum2) {
	if (i == n) {
		return abs(sum1 - sum2);
	}
	return min(
		solve(i + 1, sum1 + weight[i], sum2),
		solve(i + 1, sum1, sum2 + weight[i])
	);
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> weight[i];
	}
	cout << solve(0, 0, 0) << endl;
}