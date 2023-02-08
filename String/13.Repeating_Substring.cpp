/*
A repeating substring is a substring that occurs in two (or more) locations in the string. Your task is to find the longest repeating substring in a given string.

Input

The only input line has a string of length n that consists of characters a–z.

Output

Print the longest repeating substring. If there are several possibilities, you can print any of them. If there is no repeating substring, print −1.

Constraints

    1≤n≤105


Example

Input:
cabababc

Output:
abab
*/
/*
First, build a suffix array and a corresponding LCP array over the string  . A longest repeating substring must be between two adjacent suffixes in the suffix array, so the length of the answer is simply the maximum number in the LCP array. 
*/

/*
Problem Name: Repeating Substring
Problem Link: https://cses.fi/problemset/task/2106
Author: Sachin Srivastava (mrsac7)
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 1e5+5;
int sa[mxN], pos[mxN], tmp[mxN], lcp[mxN];
int gap, N;
string S;

bool comp(int x, int y) {
    if (pos[x] != pos[y])
        return pos[x] < pos[y];
    x += gap;
    y += gap;
    return (x < N && y < N) ? pos[x] < pos[y] : x > y;
}

void suffix() {
    for (int i = 0; i < N; i++)
        sa[i] = i, pos[i] = S[i];

    for (gap = 1;; gap <<= 1) {
        sort(sa, sa+N, comp);
        for (int i = 0; i < N-1; i++)
            tmp[i+1] = tmp[i] + comp(sa[i], sa[i+1]);
        for (int i = 0; i < N; i++)
            pos[sa[i]] = tmp[i];
        if (tmp[N - 1] == N - 1)
            break;
    }
}

void build_lcp() {
    for (int i = 0, k = 0; i < N; i++) if (pos[i] != N-1) {
        int j = sa[pos[i] + 1];
        while (S[i + k] == S[j + k])
            k++;
        lcp[pos[i]] = k;
        if (k) k--;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    cin>>S; N = S.size();
    suffix();
    build_lcp();
    int mx = max_element(lcp, lcp+N) - lcp;
    if (lcp[mx] == 0) return cout<<-1, 0;
    cout << S.substr(sa[mx], lcp[mx]);
}