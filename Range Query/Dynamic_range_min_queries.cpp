/*
Given an array of n integers, your task is to process q queries of the following types:

    update the value at position k

to u

what is the minimum value in range [a,b]

    ?

Input

The first input line has two integers n and q: the number of values and queries.

The second line has n integers x1,x2,…,xn: the array values.

Finally, there are q lines describing the queries. Each line has three integers: either "1 k u" or "2 a b".

Output

Print the result of each query of type 2.

Constraints

    1≤n,q≤2⋅105


1≤xi,u≤109

1≤k≤n

1≤a≤b≤n


Example

Input:
8 4
3 2 4 5 1 1 5 3
2 1 4
2 5 6
1 2 3
2 1 4

Output:
2
1
3
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

/** A data structure that can answer point update & range minimum queries. */
template<class T>
class MinSegmentTree {
	private:
		/** The operation to use for combining two elements. (Must be associative) */
		T comb(T a, T b) { return std::min(a, b); }
		const T DEFAULT = 1e18;  // Will overflow if T is an int

		vector<T> segtree;
		int len;
	public:
		MinSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) { }

		/** Sets the value at ind to val. */
		void set(int ind, T val) {
			assert(0 <= ind && ind < len);
			ind += len;
			segtree[ind] = val;
			for (; ind > 1; ind /= 2) {
				segtree[ind >> 1] = comb(segtree[ind], segtree[ind ^ 1]);
			}
		}

		/** @return the minimum element in the range [start, end) */
		T range_min(int start, int end) {
			assert(0 <= start && start < len && 0 < end && end <= len);
			T sum = DEFAULT;
			for (start += len, end += len; start < end; start /= 2, end /= 2) {
				if ((start & 1) != 0) {
					sum = comb(sum, segtree[start++]);
				}
				if ((end & 1) != 0) {
					sum = comb(sum, segtree[--end]);
				}
			}
			return sum;
		}
};

int main() {
	int arr_len;
	int query_num;
	std::cin >> arr_len >> query_num;

	MinSegmentTree<int> segtree(arr_len);
	for (int i = 0; i < arr_len; i++) {
		int n;
		std::cin >> n;
		segtree.set(i, n);
	}

	for (int q = 0; q < query_num; q++) {
		int type;
		std::cin >> type;
		if (type == 1) {
			int ind;
			int val;
			std::cin >> ind >> val;
			segtree.set(ind - 1, val);
		} else if (type == 2) {
			int start;
			int end;
			std::cin >> start >> end;
			cout << segtree.range_min(start - 1, end) << '\n';
		}
	}
}