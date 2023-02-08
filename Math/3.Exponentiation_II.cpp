/*
Your task is to efficiently calculate values abc modulo 109+7.

Note that in this task we assume that 00=1.

Input

The first input line has an integer n: the number of calculations.

Afther this, there are n lines, each containing three integers a, b and c.

Output

Print each value abc modulo 109+7.

Constraints

    1≤n≤105


0≤a,b,c≤109


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

		ll pow_bc = binpow(b, c, MOD - 1);
		ll ans = binpow(a, pow_bc, MOD);

		cout << ans << '\n';
	}
}