

/*
Given an array of n integers, your task is to find the maximum sum of values in a contiguous subarray with length between a and b.

Input

The first input line has three integers n, a and b: the size of the array and the minimum and maximum subarray length.

The second line has n integers x1,x2,…,xn: the array values.

Output

Print one integer: the maximum subarray sum.

Constraints

    1≤n≤2⋅105


1≤a≤b≤n

−109≤xi≤109


Example

Input:
8 1 2
-1 3 -2 5 3 -5 2 2

Output:
8
*/

/*
We are asked to find the maximum subarray with size in 
$[a,b]$
.


Hint 1

We can observe that we will be performing sum range queries for our subarray.

Therefore, we should construct a prefix sum array to perform these queries.

Notice that we are trying to maximize $\textrm{pfx}[i] - \textrm{pfx}[j]$. Since
$j$ is guaranteed to be within the window $[i-b,i]$, we can construct a sliding
window of size b, and compute
$\max_{A\le i \le B}(\textrm{pfx}[i]-\textrm{pfx}[j])$.
Implementation using a multiset in C++:
*/

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll LINF = 1e18;

int N, A, B;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> A >> B; // reading in variables

	vector<long long> pfx(N+1);
	for(int i = 1; i <= N; i++) {
		int a; cin >> a;
		pfx[i] = a + pfx[i-1]; // construction of our prefix sum
	}

	ll ret = -LINF;
	multiset<ll> ms;

	// we can keep a sliding window of size B, then find the lowest pfx[j] using multiset
	for(int i = A; i <= N; ++i) {
		if(i > B) ms.erase(ms.find(pfx[i-B-1])); //erase the element if size > B
		ms.insert(pfx[i-A]);
		ret = max(ret, pfx[i]-*ms.begin()); //we want to minimize ms.begin() aka pfx[j]
	}

	cout << ret << "\n";
}