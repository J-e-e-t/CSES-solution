/*
     Time limit: 1.00 s Memory limit: 512 MB 

A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of abcababcab are ab and abcab.

Your task is to find all border lengths of a given string.

Input

The only input line has a string of length n consisting of characters a–z.

Output

Print all border lengths of the string in increasing order.

Constraints

    1≤n≤106


Example

Input:
abcababcab

Output:
2 5
*/

/*
This problem can be done with hashing. We will hash the entire string, and for each prefix we check if the corresponding suffix has the same hash value
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll R = 9973, MOD = 99999989;

string S;
ll H[1000005], P = 1;
 
int main() {
	cin >> S;
	for (int i = 0; i < S.size(); i++) 
		H[i] = ((i == 0 ? 0 : H[i - 1]) * R + (ll)S[i]) % MOD;
 
	for (int k = 1; k < (int)S.size(); k++) {
		P = (P * R) % MOD;
		ll suf = (H[S.size() - 1] - (P * H[S.size() - k - 1]) % MOD + MOD) % MOD;
		if (H[k - 1] == suf)
			cout << k << ' ';
	}
	cout << '\n';
}

