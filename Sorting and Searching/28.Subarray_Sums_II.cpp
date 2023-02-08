/*
Given an array of n integers, your task is to count the number of subarrays having sum x.

Input

The first input line has two integers n and x: the size of the array and the target sum x.

The next line has n integers a1,a2,…,an: the contents of the array.

Output

Print one integer: the required number of subarrays.

Constraints

    1≤n≤2⋅105


−109≤x,ai≤109


Example

Input:
5 7
2 -1 3 5 -2

Output:
2
*/
/*
Problem

We are asked to find the number of subarrays that sum up to $x$ given the size
of the array and its elements.

*/

//Time Complexity:
 
// $\mathcal{O}(N \log N)$

#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * @author Qi Wang
 * (detemplifying courtesy to Kevin Sheng)
 */
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, X;
	cin >> N >> X;
	vector<int> T(N);
	for (int i = 0; i < N; i++) {
		cin >> T[i];
	}

	long long prefix_sum = 0;
	long long ans = 0;
	map<long long, int> sums;
	sums[0] = 1;
	for (int x : T) {
		prefix_sum += x;
		/*
		 * If there is a subarray with a prefix sum of prefix_sum - X,
		 * we can exclude it from our current subarray to get the desired sum.
		 * Thus, we can add the number of those subarrays to our answer.
		 */
		ans += sums[prefix_sum - X];
		// Increment the amount of prefix sums with a sum of prefix_sum
		sums[prefix_sum]++;
	}
	cout << ans << endl;
}