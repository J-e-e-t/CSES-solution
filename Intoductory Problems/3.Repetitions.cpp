/*
You are given a DNA sequence: a string consisting of characters A, C, G, and T. Your task is to find the longest repetition in the sequence. This is a maximum-length substring containing only one type of character.

Input

The only input line contains a string of n characters.

Output

Print one integer: the length of the longest repetition.

Constraints

    1≤n≤106


Example

Input:
ATTCGGGA

Output:
3
*/

#include <bits/stdc++.h>
using namespace std;
#define REP(i, a, n) for (int i = a; i < n; i++)
#define ll long long
 
int main()
{
    string s, a;
    a = "ATCG";
    cin >> s;
 
    int cnt = 0;
    int t = 0;
    //ATTCGAAAATC
    REP(i, 0, 4)
    {
        char x = a[i];
        t=0;
        REP(i, 0, s.size())
        {
 
            if (s[i] == x)
            {
                t++;
                cnt = max(cnt, t);
            }
            else
            {
                t = 0;
            }
        }
    }
    cout<<cnt;
}