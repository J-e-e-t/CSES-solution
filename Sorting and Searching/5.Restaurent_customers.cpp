/*
You are given the arrival and leaving times of n customers in a restaurant.

What was the maximum number of customers in the restaurant at any time?

Input

The first input line has an integer n: the number of customers.

After this, there are n lines that describe the customers. Each line has two integers a and b: the arrival and leaving times of a customer.

You may assume that all arrival and leaving times are distinct.

Output

Print one integer: the maximum number of customers.

Constraints

    1≤n≤2⋅105


1≤a<b≤109


Example

Input:
3
5 8
2 4
3 9

Output:
2
*/

// https://usaco.guide/problems/cses-1619-restaurant-customers/solution

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<int, int>> times;
	for (int i = 0; i < n; i++) {
		int start, end;
		cin >> start >> end;
		times.push_back({start, 1});
		times.push_back({end, -1});
	}

	sort(times.begin(), times.end());

	int curr_ppl = 0;
	int max_ppl = 0;
	for (const pair<int, int>& t : times) {
		curr_ppl += t.second;
		max_ppl = max(max_ppl, curr_ppl);
	}

	cout << max_ppl << endl;
}