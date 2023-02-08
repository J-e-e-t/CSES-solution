/*
Given a string, your task is to determine the longest palindromic substring of the string. For example, the longest palindrome in aybabtu is bab.

Input

The only input line contains a string of length n. Each character is one of a–z.

Output

Print the longest palindrome in the string. If there are several solutions, you may print any of them.

Constraints

    1≤n≤106


Example

Input:
aybabtu

Output:
bab
*/
/*
This is a textbook application of Manacher's Algorithm.

Interestingly enough, a shorter code can be attained by simply inserting a special character between two adjacent indicies (so "baacba" would become "b#a#a#c#b#a") then running the odd case of Manacher's Algorithm. 
*/

#include <bits/stdc++.h>
using namespace std;
 
string S;
int d1[1000005], d2[1000005];
 
int main() {
    cin >> S;
 
    int n = S.size();
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && S[i - k] == S[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
 
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && S[i - k - 1] == S[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
 
    int ans = 0, ind = -1;
    for (int i = 0; i < n; i++) {
        if (d1[i] * 2 - 1 > ans) 
            ans = d1[i] * 2 - 1, ind = i;
        if (d2[i] * 2 > ans)
            ans = d2[i] * 2, ind = i;
    }
    if (ans % 2 == 1)
        cout << S.substr(ind - ans / 2, ans);
    else 
        cout << S.substr(ind - ans / 2, ans);
}