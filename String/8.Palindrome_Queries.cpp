/*
You are given a string that consists of n characters between a–z. The positions of the string are indexed 1,2,…,n.

Your task is to process m operations of the following types:

    Change the character at position k

to x

Check if the substring from position a
to position b

    is a palindrome

Input

The first input line has two integers n and m: the length of the string and the number of operations.

The next line has a string that consists of n characters.

Finally, there are m lines that describe the operations. Each line is of the form "1 k x" or "2 a b".

Output

For each operation 2, print YES if the substring is a palindrome and NO otherwise.

Constraints

    1≤n,m≤2⋅105


1≤k≤n

1≤a≤b≤n


Example

Input:
7 5
aybabtu
2 3 5
1 3 x
2 3 5
1 5 x
2 3 5

Output:
YES
NO
YES
*/
/*
We will build two segment trees over the hashes: one forward and one backwards. Updates correspond to updates on the segment tree, and queries are just comparing the (adjusted) hash values on the two segment trees, as palindromes are defined to be a string that is the same forward and backwards.

*/
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const ll HASH =  257, MOD = 1e9 + 7;
 
int N, Q;
ll powH[200005] = {1};
 
namespace forward_hash {
    ll T[400005];
 
    void update(int i, ll v) {
        for (T[i += N] = v; i > 1; i >>= 1)
            T[i >> 1] = (T[i] + T[i ^ 1]) % MOD;
    }
 
    ll query(int l, int r) {
        ll res = 0;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = (res + T[l++]) % MOD;
            if (r & 1) res = (res + T[--r]) % MOD;
        }
        return res;
    }
}
 
namespace backward_hash {
    ll T[400005];
 
    void update(int i, ll v) {
        for (T[i += N] = v; i > 1; i >>= 1)
            T[i >> 1] = (T[i] + T[i ^ 1]) % MOD;
    }
 
    ll query(int l, int r) {
        ll res = 0;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = (res + T[l++]) % MOD;
            if (r & 1) res = (res + T[--r]) % MOD;
        }
        return res;
    }
}
 
int main() {
    cin >> N >> Q;
    for (int i = 1; i < N; i++) {
        powH[i] = (powH[i - 1] * HASH) % MOD;
        //cout << powH[i] << " \n"[i == N - 1];
    }
    for (int i = 0; i < N; i++) {
        char c; cin >> c;
        forward_hash::update(i, powH[i] * (ll)c % MOD);
        backward_hash::update(i, powH[N - i - 1] * (ll)c % MOD);
    }
 
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int k; char c;
            cin >> k >> c;
            k--;
            forward_hash::update(k, powH[k] * (ll)c % MOD);
            backward_hash::update(k, powH[N - k - 1] * (ll)c % MOD);
        }
        else if (t == 2) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            ll forward = forward_hash::query(l, r);
            forward = (forward * powH[N - 1 - r]) % MOD;
            ll backward = backward_hash::query(l, r);
            backward = (backward * powH[l]) % MOD;
            if (forward == backward)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}