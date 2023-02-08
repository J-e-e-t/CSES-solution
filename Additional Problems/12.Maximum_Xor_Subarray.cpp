/*
Given an array of n integers, your task is to find the maximum xor sum in a subarray.

Input

The first input line has an integer n: the size of the array.

The next line has n integers x1,x2,…,xn: the contents of the array.

Output

Print one integer: the maximum xor sum in a subarray.

Constraints

    1≤n≤2⋅105


0≤xi≤109


Example

Input:
4
5 1 5 9

Output:
13
*/
#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *c[2];
};

int N, xum, best;
Node *root;

void update(int x){
    Node *cur = root;
    for(int i = 30; i >= 0; i--){
        if(x&(1<<i)){
            if(!cur->c[1])  cur->c[1] = new Node();
            cur = cur->c[1];
        } else {
            if(!cur->c[0])  cur->c[0] = new Node();
            cur = cur->c[0];
        }
    }
}

int query(int x){
    int res = 0;
    Node *cur = root;
    for(int i = 30; i >= 0; i--){
        if(x&(1<<i)){
            if(cur->c[0]){
                res += (1<<i);
                cur = cur->c[0];
            } else cur = cur->c[1];
        } else {
            if(cur->c[1]){
                res += (1<<i);
                cur = cur->c[1];
            } else cur = cur->c[0];
        }
    }
    return res;
}

int main(){
    scanf("%d", &N);
    root = new Node();
    update(0);
    for(int i = 0, x; i < N; i++){
        scanf("%d", &x);
        xum ^= x;
        update(xum);
        best = max(best, query(xum));
    }
    printf("%d\n", best);
}
