/*
There are apples and bananas and each of them has an integer weight between 1…k. Your task is to calculate for each weight w between 2...2k the number of ways we can choose an apple and a banana whose combined weight is w.

Input

The first input line contains three integers k, n and m: the number k, the number of apples and the number of bananas.

The next line contains n integers a1,a2,…,an: weight of each apple.

The last line contains m integers b1,b2,…,bm: weight of each banana.

Output

For each integer w between 2…2k print the number of ways to choose an apple and a banana whose combined weight is w.

Constraints

    1≤k,n,m≤2⋅105


1≤ai≤k

1≤bi≤k


Example

Input:
5 3 4
5 2 5
4 3 2 3

Output:
0 0 1 2 1 2 4 2 0

Explanation: For example for w = 8 there are 4 different ways: we can pick an apple of weight 5 in two different ways and a banana of weight 3 in two different ways. 
*/
#include <bits/stdc++.h>

using namespace std;
typedef double ld;
typedef complex<ld> cd;
const int SIZE = 1<<19;
const ld PI = acos(-1);

int N, M, K;
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
    scanf("%d %d %d", &K, &N, &M);
    for(int i = 0, x; i < N; i++){
        scanf("%d", &x);
        A[x] += 1;
    }
    for(int i = 0, x; i < M; i++){
        scanf("%d", &x);
        B[x] += 1;
    }

    fft(A, false);
    fft(B, false);
    for(int i = 0; i < SIZE; i++)
        A[i] *= B[i];
    fft(A, true);

    for(int i = 2; i <= 2*K; i++)
        printf("%lld%c", llround(A[i].real()), (" \n")[i==2*K]);
}