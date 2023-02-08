/*
A fence consists of n vertical boards. The width of each board is 1 and their heights may vary.

You want to attach a rectangular advertisement to the fence. What is the maximum area of such an advertisement?

Input

The first input line contains an integer n: the width of the fence.

After this, there are n integers k1,k2,…,kn: the height of each board.

Output

Print one integer: the maximum area of an advertisement.

Constraints

    1≤n≤2⋅105


1≤ki≤109


Example

Input:
8
4 1 5 3 3 2 4 1

Output:
10
*/

/*
The largest rectangle must have the same height as the shortest bar that it
contains. For each $i$, consider the largest rectangle with height $H[i]$ such
that bar $i$ is the shortest bar it contains. The answer is simply the largest
of these $N$ rectangles.

Since the heights of these rectangles are fixed, we just want them to be as wide
as possible. Notice how the rectangle of bar $i$ is bounded by the the closest
shorter bars on each side of bar $i$ (or the ends of the histogram if these bars
don't exist).

We can use a monotone stack twice to find the closest shorter bars on each side
of each bar. See
the stacks module
for more details.
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	long long largestRectangleArea(vector<long long>& heights) {
		int n = heights.size();
		if (!n) return 0;
		stack<long long> stck;
		vector<long long> area(n, 0);
		for (int i = 0; i < n; i++) {
			while (stck.size() && heights[stck.top()] >= heights[i]) stck.pop();
			long long width = i - (stck.size() ? stck.top() : -1);
			area[i] += width * heights[i];
			stck.push(i);
		}
		while (stck.size()) stck.pop();
		for (int i = n - 1; ~i; i--) {
			while (stck.size() && heights[stck.top()] >= heights[i]) stck.pop();
			long long width = (stck.size() ? stck.top() : n) - i;
			area[i] += (width - 1) * heights[i];
			stck.push(i);
		}
		return *max_element(area.begin(), area.end());
	}
};

int main(){
	int n;
	cin>>n;

	vector<long long> heights(n);

	for(int i=0;i<n;i++){
		cin>>heights[i];
	}
	Solution* obj = new Solution();
	cout<<obj->largestRectangleArea(heights);
}