/*
You are given a string of length n. If all of its distinct substrings are ordered lexicographically, what is the kth smallest of them?

Input

The first input line has a string of length n that consists of characters a–z.

The second input line has an integer k.

Output

Print the kth smallest distinct substring in lexicographical order.

Constraints

    1≤n≤105


1≤k≤n(n+1)2

It is guaranteed that k

    does not exceed the number of distinct substrings.

Example

Input:
babaacbaab
10

Output:
aba

Explanation: The 10 smallest distinct substrings in order are a, aa, aab, aac, aacb, aacba, aacbaa, aacbaab, ab, and aba. */

//Using suffix automata, the solution becomes quite straightforward. An in-depth look can be found https://cp-algorithms.com/string/suffix-automaton.html#toc-tgt-18.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SuffixAuto {
    struct State {
        int len, link;
        int next[26];
        State(int _len = 0, int _link = -1) : len(_len), link(_link) {
            memset(next, -1, sizeof(next));
        }
    };
 
    vector<State> states;
    int last;
 
    SuffixAuto() {}
 
    SuffixAuto(const string &S) {
        init(S);
    }
 
    inline int state(int len = 0, int link = -1) {
        states.emplace_back(len, link);
        return states.size() - 1;
    }
 
    void init(const string &S) {
        states.reserve(2 * S.size());
        last = state();
        for (char c : S)
            extend(c);
    }
 
    void extend(char _c) {
        int c = _c - 'a'; // change for different alphabet
        int cur = state(states[last].len + 1), P = last; 
        while (P != -1 && states[P].next[c] == -1) {
            states[P].next[c] = cur;
            P = states[P].link;
        }
        if (P == -1)
            states[cur].link = 0;
        else {
            int Q = states[P].next[c];
            if (states[P].len + 1 == states[Q].len)
                states[cur].link = Q;
            else {
                int C = state(states[P].len + 1, states[Q].link);
                copy(states[Q].next, states[Q].next + 26, states[C].next);
                while (P != -1 && states[P].next[c] == Q) {
                    states[P].next[c] = C;
                    P = states[P].link;
                }
                states[Q].link = states[cur].link = C;
            }
        }
        last = cur;
    }
};
 
string S;
SuffixAuto sa;
ll N, dp[200005];
 
ll dfs_dp(int u = 0) {
    if (dp[u] > 0)
        return dp[u];
    for (int i = 0; i < 26; i++)
        if (sa.states[u].next[i] != -1) 
            dp[u] += dfs_dp(sa.states[u].next[i]);
    return dp[u] += 1;
}
 
string p = "";
 
void dfs(int u = 0) {
    if (N == 0) 
        return;
    else 
        N--;
    for (int i = 0; i < 26; i++) {
        int v = sa.states[u].next[i];
        if (v != -1) {
            if (N >= dp[v]) {
                N -= dp[v];
            }
            else {
                p += (char)(i + 'a');
                return dfs(v);
            }
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    cin >> S >> N;
    sa.init(S);
    dfs_dp();
    dfs();
    cout << p << '\n';
}