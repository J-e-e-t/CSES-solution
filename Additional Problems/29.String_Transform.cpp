/*
Consider the following string transformation:

    append the character # to the string (we assume that # is lexicographically smaller than all other characters of the string)
    generate all rotations of the string
    sort the rotations in increasing order
    based on this order, construct a new string that contains the last character of each rotation

For example, the string babc becomes babc#. Then, the sorted list of rotations is #babc, abc#b, babc#, bc#ba, and c#bab. This yields a string cb#ab.

Input

The only input line contains the transformed string of length n+1. Each character of the original string is one of a–z.

Output

Print the original string of length n.

Constraints

    1≤n≤106


Example

Input:
cb#ab

Output:
babc
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e6+5;

int N, nxt[maxN];
char S[maxN];

int main(){
    scanf(" %s", S);
    N = (int) strlen(S);
    for(int i = 0; i < N; i++)  nxt[i] = i;
    stable_sort(nxt, nxt+N, [](int a, int b){
        return S[a] < S[b];
    });

    int ptr = nxt[0];
    while(ptr != 0){
        ptr = nxt[ptr];
        printf("%c", S[ptr]);
    }
}