/*     Time limit: 1.00 s Memory limit: 512 MB 

You are given an array containing n positive integers.

Your task is to divide the array into k subarrays so that the maximum sum in a subarray is as small as possible.

Input

The first input line contains two integers n and k: the size of the array and the number of subarrays in the division.

The next line contains n integers x1,x2,…,xn: the contents of the array.

Output

Print one integer: the maximum sum in a subarray in the optimal division.

Constraints

    1≤n≤2⋅105


1≤k≤n

1≤xi≤109


Example

Input:
5 3
2 4 7 3 5

Output:
8

Explanation: An optimal division is [2,4],[7],[3,5] where the sums of the subarrays are 6,7,8. The largest sum is the last sum 8.*/

/*
Explanation

In this problem, we're asked to divide an array into $k$ subarrays such that the
maximum sum of a subarray is minimized.

Let's begin by making an important observation. First of all, if you can divide
an array such that the maximum sum is at most $x$, you can also divide the array
such that the maximum sum is at most $y > x$ with the same division.

Now, given some maximum sum $x$, we can check whether a division is possible
using a greedy algorithm. If we can divide the array into $s < k$ subarrays,
then we can divide it into $k$ subarrays without increasing the maximum sum of a
subarray. Therefore, we can greedily create subarrays as long as the sum of the
subarray does not exceed $x$, and check if the number of subarrays is $\leq k$.

Time Complexity: $\mathcal{O}(N \log N)$

Warning!

Make sure to use long longs to avoid overflow! Implementing the greedy algorithm also requires some caution.
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k; cin >> n >> k;
	vector<ll> a(n);
	// The maximum sum possible is the sum of all the elements in the vector.
	ll max_sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		max_sum = max_sum + a[i];
	}

	ll lo = 0, hi = max_sum, ans = 0;
	auto works = [&] (ll mid) {
		int groups = 0;
		ll sum = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] > mid) {
				return false;
			}
			if (sum + a[i] > mid) {
				++groups;
				sum = 0;
			}
			sum += a[i];
		}
		if (sum > 0) {
			++groups;
		}
		return groups <= k;
	};
	while (lo <= hi) {
		ll mid = (lo + hi) / 2;
		if (works(mid)) {
			hi = mid - 1;
			ans = mid;
		}
		else {
			lo = mid + 1;
		}
	}
	cout << ans << '\n';
}