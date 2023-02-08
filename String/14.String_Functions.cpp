/*
We consider a string of n characters, indexed 1,2,…,n. Your task is to calculate all values of the following functions:

    z(i)

denotes the maximum length of a substring that begins at position i and is a prefix of the string. In addition, z(1)=0
.
π(i)
denotes the maximum length of a substring that ends at position i, is a prefix of the string, and whose length is at most i−1

    .

Note that the function z is used in the Z-algorithm, and the function π is used in the KMP algorithm.

Input

The only input line has a string of length n. Each character is between a–z.

Output

Print two lines: first the values of the z function, and then the values of the π function.

Constraints

    1≤n≤106


Example

Input:
abaabca

Output:
0 0 1 2 0 0 1
0 0 1 1 2 0 1
*/

/*
This problem is very straightforward. Tutorials for the prefix function and z-function can be found https://cp-algorithms.com/string/prefix-function.html and https://cp-algorithms.com/string/z-function.html*/

#include <bits/stdc++.h>
using namespace std;

namespace str {
    vector<int> pi(const string &s) {
        int n = (int)s.length();
        vector<int> _pi(n);
        for (int i = 1, j; i < n; i++) {
            for (j = _pi[i - 1]; j > 0 && s[j] != s[i]; j = _pi[j - 1]);
            if (s[i] == s[j])
                j++;
            _pi[i] = j;
        }
        return _pi;
    }
 
    vector<int> z(const string &s) {
        int n = (int)s.size();
        vector<int> _z(n);
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i <= r)
                _z[i] = min(_z[i - l], r - i + 1);
            while (i + _z[i] < n && s[_z[i]] == s[i + _z[i]])
                _z[i]++;
            if (i + _z[i] - 1 > r)
                l = i, r = i + _z[i] - 1;
        }
        return _z;
    }
}

string S;
 
int main() { 
    cin >> S;
    vector<int> z = str::z(S);
    for (int x : z)
        cout << x << ' ';
    cout << '\n';
    vector<int> pi = str::pi(S);
    for (int x : pi)
        cout << x << ' ';
    cout << '\n';
}