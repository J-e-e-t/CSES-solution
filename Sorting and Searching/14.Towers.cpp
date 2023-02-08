/*
     Time limit: 1.00 s Memory limit: 512 MB 

You are given n cubes in a certain order, and your task is to build towers using them. Whenever two cubes are one on top of the other, the upper cube must be smaller than the lower cube.

You must process the cubes in the given order. You can always either place the cube on top of an existing tower, or begin a new tower. What is the minimum possible number of towers?

Input

The first input line contains an integer n: the number of cubes.

The next line contains n integers k1,k2,…,kn: the sizes of the cubes.

Output

Print one integer: the minimum number of towers.

Constraints

    1≤n≤2⋅105


1≤ki≤109


Example

Input:
5
3 8 2 1 5

Output:
2*/


/*
Greedy approach: always add the next cube on top of the tower with the smallest
possible cube on top (or create a new tower if this isn't possible).

Equivalent to longest non-decreasing subsequence!

It's important to note that we cannot use brute force to find the tower with the
smallest possible cube on top because that will yield a time complexity of
$\mathcal{O}(N^2)$, which is too slow.

Solution 1 - Binary Search + Dynamic Array

Time Complexity: $\mathcal{O}(N\log N)$

We can store existing towers using a dynamic array, where each tower's value is
the size of the cube on top. For each cube, we can run upper bound binary search
on the array to find the tower with the smallest top cube that's strictly larger
than the current cube. If we find a suitable tower, we add the cube to the top
and change the tower's value to the size of the cube. If no such tower exists,
append a new tower to the end of the array. By doing so, we maintain the tower
array in a sorted order (try and prove this for yourself). Our answer will be
the size of the array after all cubes have been processed.

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define pb push_back
#define sz(x) (int)(x).size()

int n;
vi x; // stores towers in non-decreasing order

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int z; cin >> z;
		int lo = 0, hi = sz(x);
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (x[mid] > z) hi = mid;
			else lo = mid + 1;
		}
		if (lo == sz(x)) x.pb(z); // create new tower
		else x[lo] = z; // add to tower
	}
	cout << sz(x);
}

*/

/*
Solution 2 - Multiset

Time Complexity: $\mathcal{O}(N\log N)$

In this approach, we store the towers using an ordered multiset (which can be
represented as a
TreeMap in
Java), where each tower's value is the size of the cube on top. For each cube,
we can use built-in methods (upper_bound in C++, higherKey in Java) to find
the smallest-valued tower with a value strictly greater than the cube. If we
find a suitable tower, we add the cube to the top and change the tower's value
to the size of the cube by removing the tower's previous value from the set and
adding it's new value into it. If no such tower exists, we add a new tower to
the set. Our answer will be the total number of towers in the multiset (this
takes some extra work to find in Java) after all cubes have been processed.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n;
	multiset<int> ans;
	for (int i = 0; i < n; ++i) {
		cin >> k;
		auto it = ans.upper_bound(k);
		// Find the tower having the element that is just larger than k to add
		// k to. If it doesn't exist then we create a new tower.
		if (it == ans.end()) ans.insert(k);
		else {
			// If there exists a satisfying tower, add k to that tower and
			// update the top element of the tower
			ans.erase(it);
			ans.insert(k);
		}
	}
	cout << ans.size();
	return 0;
}