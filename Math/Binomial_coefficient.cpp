/*
Your task is to calculate n binomial coefficients modulo 109+7.

A binomial coefficient (ab) can be calculated using the formula a!b!(a−b)!. We assume that a and b are integers and 0≤b≤a.

Input

The first input line contains an integer n: the number of calculations.

After this, there are n lines, each of which contains two integers a and b.

Output

Print each binomial coefficient modulo 109+7.

Constraints

    1≤n≤105


0≤b≤a≤106


Example

Input:
3
5 3
8 1
9 5

Output:
10
8
126
*/

/*
Since these binomial coefficients are large, problems typically require us to output the answer modulo a large prime 
$p$
 such as 
$10^9 + 7$
. Fortunately, we can use 
modular inverses
 to divide 
$n!$
 by 
$k!$
 and 
$(n - k)!$
 modulo 
$p$
 for any prime 
$p$
. Computing inverse factorials 
online
 can be very time costly. Instead, we can 
precompute
 all factorials in 
$\mathcal{O}(n)$
 time and inverse factorials in 
$\mathcal{O}(n + \log MOD)$
. First, we compute the modular inverse of the largest factorial using binary exponentiation. For the rest, we use the fact that 
$(n!)^{-1} = (n!)^{-1} * (n+1)^{-1} * (n+1) =((n+1)!)^{-1}*(n+1)$
. See the code below for the implementation.
*/
#include <iostream>
using namespace std;
using ll = long long;

const int MAXN = 1e6;
const int MOD = 1e9 + 7;

ll fac[MAXN + 1];
ll inv[MAXN + 1];

//BeginCodeSnip{Counting functions}
ll exp(ll x, ll y, ll p) {
	ll res = 1; x %= p;
	while (y) {
		if (y & 1) {
			res *= x; res %= p; 
		}
		x *= x;
		x %= p;
		y >>= 1;
	}
	return res;
}

void factorial() {
	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) {
		fac[i] = fac[i - 1] * i % MOD;
	}
}

void inverses() {
	inv[MAXN] = exp(fac[MAXN], MOD - 2, MOD);
	for (int i = MAXN; i >= 1; i--) {
		inv[i - 1] = inv[i] * i % MOD;
	}
}

ll choose(int n, int r) {
	return fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}
//EndCodeSnip

int main() {
	factorial();
	inverses();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		cout << choose(a, b) << '\n';
	}
}