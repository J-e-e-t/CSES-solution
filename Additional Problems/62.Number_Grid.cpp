/*
Consider a two-dimensional grid whose rows and columns are 1-indexed. Each square contains the smallest nonnegative integer that does not appear to the left on the same row or above on the same column.

Your task is to calculate the value at square (y,x).

Input

The only input line contains two integers y and x.

Output

Print one integer: the value at square (y,x).

Constraints

    1≤y,x≤109


Example

Input:
3 5

Output:
6*/
#include <bits/stdc++.h>

using namespace std;

int x, y;

int main(){
    scanf("%d %d", &x, &y);
    printf("%d\n", (x-1)^(y-1));
}
