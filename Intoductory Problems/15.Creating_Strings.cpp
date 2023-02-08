/*
Given a string, your task is to generate all different strings that can be created using its characters.

Input

The only input line has a string of length n. Each character is between a–z.

Output

First print an integer k: the number of strings. Then print k lines: the strings in alphabetical order.

Constraints

    1≤n≤8


Example

Input:
aabac

Output:
20
aaabc
aaacb
aabac
aabca
aacab
aacba
abaac
abaca
abcaa
acaab
acaba
acbaa
baaac
baaca
bacaa
bcaaa
caaab
caaba
cabaa
cbaaa
*/

#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#define lli long long int
#define li long int
#define ld long double
using namespace std;
const lli mod = 1e9 + 7;

set<string> perms;

void permutations(string prefix, string suffix)
{
    if (suffix.length() == 0)
    {
        perms.insert(prefix);
        return;
    }
    for (int i = 0; i < suffix.length(); i++)
    {
        permutations(prefix + suffix[i], suffix.substr(0, i) + suffix.substr(i + 1));
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    permutations("", s);
    cout << perms.size() << endl;
    for (auto ele : perms)
    {
        cout << ele << endl;
    }
    return 0;
}