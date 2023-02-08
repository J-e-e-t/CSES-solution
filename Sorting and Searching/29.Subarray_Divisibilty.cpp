/*
Given an array of n integers, your task is to count the number of subarrays where the sum of values is divisible by n.

Input

The first input line has an integer n: the size of the array.

The next line has n integers a1,a2,…,an: the contents of the array.

Output

Print one integer: the required number of subarrays.

Constraints

    1≤n≤2⋅105


−109≤ai≤109


Example

Input:
5
3 1 2 7 4

Output:
1*/

/*
We are asked to find the number of subarrays that are divisible by $N$. In other
words, we're supposed to find the number of subarrays with sum equal to
$0 \pmod N$.

Notice that any sum of a subarray can be represented as the difference of
two prefixes.

First, let $\texttt{sum}$ represent the prefix sum of array $a$ modulo $N$.

With our prefix sums knowledge,

$$\texttt{sum}(i, j) = \texttt{sum}(0, j) - \texttt{sum}(0, i-1)$$

Since we want to calculate the number of $\texttt{sum}(i, j)$ that equals to
$0\pmod N$, $\texttt{sum}(0, j)$ must be equal to $\texttt{sum}(0, i-1)$ for their
difference to be $0$.

Now, we calculate $\texttt{pmod}[i]$, the number of prefixes with remainder
equivalent to $i\pmod{N}$. Then the number of pairs contributed by $i$ is

$${\texttt{pmod}[i]\choose{2}} = \texttt{pmod}[i] \cdot (\texttt{pmod}[i] - 1) / 2$$

The answer is just the sum of this quantity over all $i$.
*/

//Time  - O(n)

#include <iostream>
#include <vector>

using namespace std;

/**
 * @author Qi Wang
 * (detemplifying courtesy of Kevin Sheng)
 */
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	vector<long long> M(N);
	long long psums = 0;
	M[psums] = 1;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		psums += a;
		// Remember to account for negative sums
		M[(psums % N + N) % N]++;
	}

	long long ans = 0;
	for (long long x : M) {
		/*
		 * Calculating the # of pairs.
		 * This calculates the pairs without
		 * duplicates and reverse groups.
		 */
		ans += x * (x - 1) / 2;
	}
	cout << ans << endl;
}

