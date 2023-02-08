/*
You are given a string of length n. If all of its substrings (not necessarily distinct) are ordered lexicographically, what is the kth smallest of them?

Input

The first input line has a string of length n that consists of characters a–z.

The second input line has an integer k.

Output

Print the kth smallest substring in lexicographical order.

Constraints

    1≤n≤105


1≤k≤n(n+1)2


Example

Input:
baabaa
10

Output:
ab

Explanation: The 10 smallest substrings in order are a, a, a, a, aa, aa, aab, aaba, aabaa, and ab. 
*/

/*
Build a suffix automaton on S . First, let cnt denote the number of times a state appears in the string. Initially, we let each newly created node have cnt = 1  and each cloned node have cnt = 0  

. After the suffix automaton has been created, we process the nodes in order of length from largest to smallest:

cnt[link(u)]+ = cnt[u]
 

We will create another array  dp
such that dp[u] is equal to the number of (not necessarily distinct) substrings that start at the current node. Note that
 dp[u] = cnt[u] + summation of dp[v] for all v belongs to transitions(u)
   

. We then use an approach similar to Substring Order I where we either go down a transition, or subtract $dp[v]$ from K.  
. */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pii pair<ll,ll>
string S;
ll N, cnt[200005], dp[200005];
 
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
        cnt[cur] = 1;
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
                cnt[C] = 0;
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
} sa;
 
ll dfs_dp(int u = 0) {
    if (dp[u] != 0)
        return dp[u];
    for (int i = 0; i < 26; i++) {
        int v = sa.states[u].next[i];
        if (v != -1) 
            dp[u] += dfs_dp(v);
    }
    return dp[u] += cnt[u];
}
 
string p = "";
 
void dfs(int u = 0) {
    if (N < cnt[u])
        return;
    else 
        N -= cnt[u];
    for (int i = 0; i < 26; i++) {
        int v = sa.states[u].next[i];
        if (v != -1) {
            if (N >= dp[v])
                N -= dp[v];
            else {
                p += (char)(i + 'a');
                return dfs(v);
            }
        }
    }
}
 
int main() {
    cin >> S >> N;
    sa.init(S);
 
    vector<pii> v(sa.states.size());
    for (int i = 0; i < sa.states.size(); i++)
        v[i] = {sa.states[i].len, i};
    sort(v.begin(), v.end(), greater<pii>());
    for (auto [len, id] : v)
        if (sa.states[id].link != -1)
            cnt[sa.states[id].link] += cnt[id];
    cnt[0] = 1;
 
    dfs_dp();
 
    dfs();
 
    cout << p << '\n';
}