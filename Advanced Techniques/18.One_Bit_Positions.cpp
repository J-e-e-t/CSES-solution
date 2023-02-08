/*
You are given a binary string of length n and your task is to calculate for every k between 1…n−1 the number of ways we can choose two positions i and j such that i−j=k and there is a one-bit at both positions.

Input

The only input line has a string that consists only of characters 0 and 1.

Output

For every distance k between 1…n−1 print the number of ways we can choose two such positions.

Constraints

    2≤n≤2⋅105


Example

Input:
1001011010

Output:
1 2 3 0 2 1 0 1 0
*/

#include <bits/stdc++.h>

using namespace std;
typedef double ld;
typedef complex<ld> cd;
const int maxN = 2e5+5;
const int SIZE = 1<<19;
const ld PI = acos(-1);

char S[maxN];
vector<cd> A(SIZE), B(SIZE);

void fft(vector<cd> &a, bool inv){
    int N = (int) a.size();

    for(int i = 1, j = 0; i < N; i++){
        int bit = N>>1;
        for(; j&bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if(i < j)
            swap(a[i], a[j]);
    }

    for(int len = 2; len <= N; len <<= 1){
        ld theta = 2*PI / len * (inv ? -1 : 1);
        cd wlen(cos(theta), sin(theta));
        for(int i = 0; i < N; i += len){
            cd w(1);
            for(int j = 0; j < len / 2; j++){
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if(inv)
        for(cd &z : a)
            z /= N;
}

int main(){
    scanf(" %s", S);
    int N = (int) strlen(S);
    for(int i = 0; i < N; i++){
        if(S[i] == '1'){
            A[i] += 1;
            B[N-i-1] += 1;
        }
    }

    fft(A, false);
    fft(B, false);
    for(int i = 0; i < SIZE; i++)
        A[i] *= B[i];
    fft(A, true);

    for(int i = N; i < 2*N-1; i++)
        printf("%lld%c", llround(A[i].real()), (" \n")[i==2*N-2]);
}
