/*
Let σ(n) denote the sum of divisors of an integer n. For example, σ(12)=1+2+3+4+6+12=28.

Your task is to calculate the sum ∑ni=1σ(i) modulo 109+7.

Input

The only input line has an integer n.

Output

Print ∑ni=1σ(i) modulo 109+7.

Constraints

    1≤n≤1012


Example

Input:
5

Output:
21*/


/*
Hint 1
$n=10^{12}$ implies that the desired time complexity is $\mathcal{O}(\sqrt n)$

Calculating the sum of the divisors for each number from $1$ to $n$ seems to be
impossible- even if it was doable in constant time the solution would still TLE.
What if instead of starting from the numbers, we started from the divisors
instead?

As mentioned in Hint 2, let's start from the divisors instead of the numbers.
If we consider any divisor $d$, notice that it will always occur
$\left\lfloor \frac{n}{d}\right\rfloor$ times if we list out all the divisors
of the numbers from $1$ to $n$.
So now, to get our answer all we have to do is calculate the below expression:
$$\sum_{d=1}^{n} \left\lfloor \frac{n}{d}\right\rfloor$$
But calculating this with brute force yields an $\mathcal{O}(n \sqrt{n})$

Video Solution

Note: The video solution might not be the same as other solutions. Code in C++.

https://youtu.be/JqWiWJQOQyU
*/

#include <iostream>

using std::cout;
using std::endl;

const int MOD = 1e9 + 7;
const int TWO_MOD_INV = 500000004;

/** @return The sum of all numbers in [start, end] mod MOD. */
long long total_sum(long long start, long long end) {
	return (
		(((end - start + 1) % MOD) * ((start + end) % MOD) % MOD)
		* TWO_MOD_INV % MOD
	);
}

int main() {
	long long n;
	std::cin >> n;

	long long total = 0;
	long long at = 1;
	while (at <= n) {
		long long add_amt = n / at;  // Our divisor to process
		// The largest number that still has the same value of q
		long long last_same = n / add_amt;

		total = (total + add_amt * total_sum(at, last_same)) % MOD;
		at = last_same + 1;
	}

	cout << total << endl;
}