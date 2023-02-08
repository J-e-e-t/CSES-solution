/*
You have an array that contains a permutation of integers 1,2,…,n. Your task is to sort the array in increasing order by reversing subarrays. You can construct any solution that has at most n reversals.

Input

The first input line has an integer n: the size of the array. The array elements are numbered 1,2,…,n.

The next line has n integers x1,x2,…,xn: the contents of the array.

Output

First print an integer k: the number of reversals.

After that, print k lines that describe the reversals. Each line has two integers a and b: you reverse a subarray from position a to position b.

Constraints

    1≤n≤2⋅105


Example

Input:
4
2 3 1 4

Output:
2
1 3
2 3
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 2e5+5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dist(1, (int) 2e9);

struct Node {
    bool rev;
    int value, prior, sz;
    Node *p, *l, *r;

    Node(){}
    Node(int val, int pri){
        prior = pri;
        value = val;
        sz = 1;
        p = l = r = nullptr;
    }
};

int N, X[maxN];
Node *root, *ndptr[maxN];

int sz(Node *t){    return t ? t->sz : 0;       }
int val(Node *t){   return t ? t->value : -1;   }

void flip(Node *t){
    if(!t)	return;
    t->rev ^= true;
}

void pull(Node *t){
    if(!t)	return;
    if(t->l)    t->l->p = t;
    if(t->r)    t->r->p = t;
    t->sz = sz(t->l) + sz(t->r) + 1;
}

void push(Node *t){
    if(!t)	return;
    if(t->rev){
        swap(t->l, t->r);
        flip(t->l); flip(t->r);
        t->rev = false;
    }
}

Node* merge(Node *x, Node *y){
    if(!x || !y)	return x ? x : y;

    push(x); push(y);
    if(x->prior < y->prior){
        x->r = merge(x->r, y);
        pull(x);
        return x;
    } else {
        y->l = merge(x, y->l);
        pull(y);
        return y;
    }
}

pair<Node*,Node*> split(Node *x, int k){
    if(!x)	return {nullptr, nullptr};

    pair<Node*,Node*> y = {nullptr, nullptr};
    push(x);
    if(k <= sz(x->l)){
        y = split(x->l, k);
        x->l = y.second;
        pull(x);
        y.second = x;
    } else {
        y = split(x->r, k-sz(x->l)-1);
        x->r = y.first;
        pull(x);
        y.first = x;
    }
    return y;
}

void heapify(Node *t){
    if(!t)	return;

    Node *mx = t;
    if(t->l && t->l->prior > mx->prior)	mx = t->l;
    if(t->r && t->r->prior > mx->prior)	mx = t->r;
    if(mx != t){
        swap(t->prior, mx->prior);
        heapify(mx);
    }
}

Node* build(int x, int k){
    if(k == 0)	return nullptr;

    int mid = k/2;
    Node *t = new Node(X[x+mid], dist(rng));
    ndptr[X[x+mid]] = t;
    t->l = build(x, mid);
    t->r = build(x+mid+1, k-mid-1);
    heapify(t);
    pull(t);
    return t;
}

void reverse(int x, int k){
    pair<Node*,Node*> y, z;
    y = split(root, x-1);
    z = split(y.second, k);
    flip(z.first);
    y.second = merge(z.first, z.second);
    root = merge(y.first, y.second);
    root->p = nullptr;
}

int orderOf(int v){
    Node* t = ndptr[v];

    vector<Node*> walk;
    while(t){
        walk.push_back(t);
        t = t->p;
    }
    reverse(walk.begin(), walk.end());
    for(Node* nd : walk){
        push(nd);
        pull(nd);
    }

    t = ndptr[v];
    int idx = sz(t->l);
    while(t){
        if(t->p && t == t->p->r)
            idx += sz(t->p->l) + 1;
        t = t->p;
    }
    return idx;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", &X[i]);

    root = build(0, N);

    printf("%d\n", N);
    for(int l = 1; l <= N; l++){
        int r = orderOf(l)+1;
        reverse(l, r-l+1);
        printf("%d %d\n", l, r);
    }
}