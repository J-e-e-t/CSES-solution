//https://cses.fi/problemset/task/2419

/*
Consider a xor pyramid where each number is the xor of lower-left and lower-right numbers. Here is an example pyramid:

Given the bottom row of the pyramid, your task is to find the topmost number.

Input

The first input line has an integer n: the size of the pyramid.

The next line has n integers a1,a2,…,an: the bottom row of the pyramid.

Output

Print one integer: the topmost number.

Constraints

    1≤n≤2⋅105


1≤ai≤109


Example

Input:
8
2 10 5 12 9 5 1 5

Output:
9
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 2e5+5;

int N, D, a, xum;

int two_divisibility(int x){
    int res = 0;
    while(x){
        x >>= 1;
        res += x;
    }
    return res;
}

int main(){
    scanf("%d", &N);
    D = two_divisibility(N-1);
    for(int i = 0; i < N; i++){
        scanf("%d", &a);
        int d1 = two_divisibility(i);
        int d2 = two_divisibility(N-i-1);
        if(D - d1 - d2 == 0)
            xum ^= a;
    }
    printf("%d\n", xum);
}
