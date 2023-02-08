/*
Given an array of n integers, your task is to find for each array position the nearest position to its left having a smaller value.

Input

The first input line has an integer n: the size of the array.

The second line has n integers x1,x2,…,xn: the array values.

Output

Print n integers: for each array position the nearest position with a smaller value. If there is no such position, print 0.

Constraints

    1≤n≤2⋅105


1≤xi≤109


Example

Input:
8
2 5 1 4 8 3 2 5

Output:
0 1 0 3 4 3 3 7
*/

/*
Consider the following problem:

Given an array, $a$, of $N$ ($1 \le N \le 10^5$) integers, for every index
$i$, find the rightmost index $j$ such that $j < i$ and $a_i > a_j$.

To solve this, let's store a stack of pairs of $value, index$ and iterate over
the array from left to right. For some index $i$, we will compute
$\texttt{ans}[i]$, the rightmost index for $i$, as follows:

Keep popping the top element off the stack as long as $value \ge a_i$. This is
because we know that the pair containing $value$ will never be the solution to
any index $j > i$, since $a_i$ is less than or equal to than $value$ and has
an index further to the right.
If $value < a_i$, set $\texttt{ans}[i]$ to $index$, because a stack stores the
most recently added values first (or in this case, the rightmost ones),
$index$ will contain the rightmost value which is less than $a_i$. Then, add
($a_i, i$) to the stack.


The stack we used is called a monotonic stack because we keep popping off
the top element of the stack which maintains it's monotonicity (the same
property needed for algorithms like binary search) because the elements in the
stack are increasing.
*/

#include <bits/stdc++.h>

using namespace std;

int N;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	stack<pair<int, int>> stack;
	stack.push({0, 0});

	for(int i = 1; i <= N; ++i) {
		int a; cin >> a;
		while(!stack.empty() && stack.top().first >= a) stack.pop();
		cout << stack.top().second << " ";
		stack.push({a, i});
	}
}