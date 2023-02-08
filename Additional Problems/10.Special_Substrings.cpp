/*
A substring is called special if every character that appears in the string appears the same number of times in the substring.

Your task is to count the number of special substrings in a given string.

Input

The only input line has a string of length n. Every character is between a...z.

Output

Print one integer: the number of special substrings.

Constraints

    1≤n≤2⋅105


Example

Input:
abccabab

Output:
5

Explanation: The special substrings are abc, cab, abccab, bccaba and ccabab. 

*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 2e5+1;

int N, M;
char S[maxN];
bool exists[26];
map<char,int> ch;
map<vector<int>,ll> dp;

bool containsEach(vector<int> V){
    for(int i = 0; i < (int) V.size(); i++)
        if(V[i] <= 0)
            return false;
    return true;
}

int main(){
    scanf(" %s", S);
    N = (int) strlen(S);
    for(int i = 0; i < N; i++){
        int c = (int) (S[i] - 'a');
        if(!exists[c]){
            ch[S[i]] = M++;
            exists[c] = true;
        }
    }

    ll ans = 0;
    vector<int> freq(M);
    dp[freq]++;
    for(int i = 0; i < N; i++){
        int c = ch[S[i]];
        freq[c]++;
        if(containsEach(freq))
            for(int j = 0; j < M; j++)
                freq[j]--;
        ans += dp[freq];
        dp[freq]++;
    }
    printf("%lld\n", ans);
}