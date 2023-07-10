/*
You are given a DNA sequence consisting of characters A, C, G, and T.

Your task is to find the shortest DNA sequence that is not a subsequence of the original sequence.

Input

The only input line contains a DNA sequence with n characters.

Output

Print the shortest DNA sequence that is not a subsequence of the original sequence. If there are several solutions, you may print any of them.

Constraints

    1≤n≤106


Example

Input:
ACGTACGT

Output:
AAA*/


/*
Suppose we partition the string into   contiguous subsegments such that the letters GCAT all appear at least once each in each partition. Then, it is clear that all  

-character strings appear as subsequences.

We can construct such a partition greedily. Find the shortest prefix of the string that contains all characters GCAT, make that one subsegment, then recurse on the remaining string. Note that this might actually partition it into  

subsegments, where the last subsegment is ``incomplete''. The last character in each subsegment (besides the incomplete subsegment) also appears exactly once in that subsegment; greedily, if it appeared earlier in the subsegment, then we could have ended this partition earlier.

If  
is maximal, then we can show that there exists a   length string that is not a subsequence. How? We can explicitly construct it as the last character in each of the partitions, plus some character not in the incomplete subsegment (or any character, if there is no incomplete subsegment). 
*/


#include<bits/stdc++.h>
using namespace std;

// #define int long long
#define endl '\n'

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    string s; cin>>s;
    int l = 0, r = 0;
    bool a = 0, b = 0, c = 0, d = 0;
    int n = s.size();
    string ans;
    while(l < n) {
        a = 0, b = 0, c = 0, d = 0;
        a += (s[l] == 'A'); b += (s[l] == 'C');
        c += (s[l] == 'G'); d += (s[l] == 'T');
        r = l+1;
        while(r < n && a+b+c+d != 4) {
            a += (s[r] == 'A'); b += (s[r] == 'C');
            c += (s[r] == 'G'); d += (s[r] == 'T');
            r++;
        }
        if (a+b+c+d == 4)
            ans += s[r-1];
        l = r;
    }
    cerr<<a<<' '<<b<<' '<<c<<' '<<d;
    if (a+b+c+d == 4)
        ans += 'A';
    else if (!a) ans += 'A';
    else if (!b) ans += 'C';
    else if (!c) ans += 'G';
    else if (!d) ans += 'T';
    cout<<ans;
}