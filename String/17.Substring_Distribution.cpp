/*
You are given a string of length n. For every integer between 1…n you need to print the number of distinct substrings of that length.

Input

The only input line has a string of length n that consists of characters a–z.

Output

For each integer between 1…n print the number of distinct substrings of that length.

Constraints

    1≤n≤105


Example

Input:
abab

Output:
2 2 2 1
*/

/*
Let us build a suffix automata over the string S . The length of a path from the initial state S0   

corresponds to the length of a string. By definition, all substrings of the initial string are uniquely encoded. It suffices to count the number of different ways to get to any given node for all nodes in the suffix automaton.

We can take advantage of the fact that each node corresponds to exactly one set of substrings, and that each substring in a node is a suffix of another (except for the largest substring). Thus, for each node, there exists some  l,r
such that it is always possible to reach it in d belongs to [l,r]  steps and impossible if d not belongs to [l,r] . Because r  has already been conveniently computed when initializing the suffix automaton, we simply have to compute l  for each node, which is just the shortest distance, It suffices to perform a BFS on the suffix automaton*/


#include <bits/stdc++.h>
using namespace std;

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
 
    void debug(int u = 0, string s = "") {
        cout << "state " << u << " = " << s << " ->";
        for (int i = 0; i < 26; i++) 
            if (states[u].next[i] != -1)
                cout << ' ' << states[u].next[i];
        cout << '\n';
        for (int i = 0; i < 26; i++) 
            if (states[u].next[i] != -1)
                debug(states[u].next[i], s + (char)(i + 'a'));
    }
};
 
string S;
SuffixAuto sa;
int lb[200005], ans[100005];
 
int main() {
    cin >> S;
    sa.init(S);
    
    queue<int> q;
    memset(lb, -1, sizeof(lb));
 
    q.push(0);
    lb[0] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int d = lb[u];
        for (int i = 0; i < 26; i++) {
            int v = sa.states[u].next[i];
            if (v != -1 && lb[v] == -1) {
                lb[v] = d + 1;
                q.push(v);
            }
        }
    }
 
    for (int i = 1; i < sa.states.size(); i++) 
        ans[lb[i]]++, ans[sa.states[i].len + 1]--;
    
    ans[0] = 0;
    for (int i = 1; i <= S.size(); i++) {
        ans[i] += ans[i - 1];
        cout << ans[i] << ' ';
    }
    cout << '\n';
}