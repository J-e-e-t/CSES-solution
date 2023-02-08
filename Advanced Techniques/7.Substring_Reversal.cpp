/*
Given a string, your task is to process operations where you reverse a substring of the string. What is the final string after all the operations?

Input

The first input line has two integers n and m: the length of the string and the number of operations. The characters of the string are numbered 1,2,…,n.

The next line has a string of length n that consists of characters A–Z.

Finally, there are m lines that describe the operations. Each line has two integers a and b: you reverse a substring from position a to position b.

Output

Print the final string after all the operations.

Constraints

    1≤n,m≤2⋅105


1≤a≤b≤n


Example

Input:
7 2
AYBABTU
3 4
4 7

Output:
AYAUTBB
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct node {
    node *L, *R;
    int W, S;
    char V;
    bool F;
    node(char x) {
        L = R = 0;
        W = rand();
        S = 1;
        V = x;
        F = 0;
    }
};

int size(node *treap) {
    return (treap == 0 ? 0 : treap->S);
}

void push(node *treap) {
    if (treap && treap->F) {
        treap->F = 0;
        swap(treap->L, treap->R);
        if (treap->L) treap->L->F ^= 1;
        if (treap->R) treap->R->F ^= 1;
    }
}

void split(node *treap, node *&left, node *&right, int k) {
    if (treap == 0)
        left = right = 0;
    else {
        push(treap);
        if (size(treap->L) < k) {
            split(treap->R, treap->R, right, k - size(treap->L) - 1);
            left = treap;
        }
        else {
            split(treap->L, left, treap->L, k);
            right = treap;
        }
        treap->S = size(treap->L) + size(treap->R) + 1;
    }
}

void merge(node *&treap, node *left, node *right) {
    if (left == 0) treap = right;
    else if (right == 0) treap = left;
    else {
        push(left);
        push(right);
        if (left->W < right->W) {
            merge(left->R, left->R, right);
            treap = left;
        }
        else {
            merge(right->L, left, right->L);
            treap = right;
        }
        treap->S = size(treap->L) + size(treap->R) + 1;
    }
}

void print(node *treap) {
    if (treap == NULL) return;
    push(treap);
    print(treap->L);
    cout << treap->V;
    print(treap->R);
}


signed main(){
    cin.tie(0)->sync_with_stdio(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    node *treap = 0;
    int n, m; cin >> n >> m;
    string s; cin >> s;
    for (auto i: s) {
        merge(treap, treap, new node(i));
    }
    while (m--) {
        int x, y; cin >> x >> y;
        node *A, *B, *C;
        split(treap, A, B, x - 1);
        split(B, B, C, y - x + 1);
        B->F ^= 1;
        merge(treap, A, B);
        merge(treap, treap, C);
    }
    print(treap);
}
