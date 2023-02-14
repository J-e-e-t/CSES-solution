/*
Your task is to efficiently calculate values a^(b^c) modulo 109+7.

Note that in this task we assume that 0^0=1.

Input

The first input line has an integer n: the number of calculations.

Afther this, there are n lines, each containing three integers a, b and c.

Output

Print each value aB^C modulo 109+7.

Constraints

    1≤n≤1e5


0≤a,b,c≤1e9


Example

Input:
3
3 7 1
15 2 2
3 4 5

Output:
2187
50625
763327764
*/
/*
Explanation

Fermat's Little Theorem tells us that $a^{p - 1} \equiv 1 \pmod{p}$, so we can calculate $a^{b^c \pmod{1e9 + 7 - 1}} \pmod{1e9+7}$ with modular exponentiation.

Implementation

Time Complexity: $\mathcal{O}(\log P)$
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long MOD = 1e9 + 7;


/*
the solution.

A Naive Approach is to calculate res = B^C and then calculate A^res % M by modular exponential. The problem of this approach is that we can’t apply directly mod M on B^C, so we have to calculate this value without mod M. But if we solve it directly then we will come up with the large value of exponent of A which will definitely overflow in final answer.
An Efficient approach is to reduce the B^C to a smaller value by using the Fermat’s Little Theorem, and then apply Modular exponential.
 

According the Fermat's little
a^(M - 1) = 1 (mod M) if M is a prime.

So if we rewrite B^C as x*(M-1) + y, then the
task of computing A^B^C becomes A^(x*(M-1) + y)
which can be written as A^(x*(M-1))*A^y.
From Fermat's little theorem, we know Ax*(M-1) = 1.
So task of computing A^B^C reduces to computing A^y

What is the value of y?
From B^C = x * (M - 1) + y,
y can be written as B^C % (M-1)

We can easily use the above theorem such that we can get
A ^ (B ^ C) % M = (A ^ y ) %  M

Now we only need to find two things as:-
1. y = (B ^ C) % (M - 1)
2. Ans = (A ^ y) % M

 

// C++ program to find (a^b) mod m for a large 'a'
#include<bits/stdc++.h>
using namespace std;
 
// Iterative Function to calculate (x^y)%p in O(log y)
unsigned int power(unsigned int x, unsigned int y,
                                   unsigned int p)
{
    unsigned int res = 1;      // Initialize result
 
    x = x % p;  // Update x if it is more than or
                // equal to p
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}
 
unsigned int Calculate(unsigned int A, unsigned int B,
                       unsigned int C, unsigned int M)
{
    unsigned int res, ans;
 
    // Calculate B ^ C (mod M - 1)
    res = power(B, C, M-1);
 
    // Calculate A ^ res ( mod M )
    ans = power(A, res, M);
 
    return ans;
}
 
// Driver program to run the case
int main()
{   // M must be a Prime Number
    unsigned int A = 3, B = 9, C = 4, M = 19;
 
    cout << Calculate(A, B, C, M);
 
    return 0;
}

Output: 

18

Time Complexity: O(log(B) + log(C)) 
Auxiliary space: O(1)

*/

//BeginCodeSnip{Binary Exponentiation}
ll binpow(ll x, ll n, ll m) {
	assert(n >= 0);
	x %= m;
	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) {  // if n is odd
			res = res * x % m;
		}
		x = x * x % m;
		n /= 2;  // divide by two
	}
	return res;
}
//EndCodeSnip

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		ll a;
		ll b;
		ll c;

		cin >> a >> b >> c;

		ll pow_BC = binpow(b, c, MOD - 1);
		ll ans = binpow(a, pow_BC, MOD);

		cout << ans << '\n';
	}
}