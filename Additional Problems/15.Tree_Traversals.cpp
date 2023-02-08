/*
There are three common ways to traverse the nodes of a binary tree:

    Preorder: First process the root, then the left subtree, and finally the right subtree.
    Inorder: First process the left subtree, then the root, and finally the right subtree.
    Postorder: First process the left subtree, then the right subtree, and finally the root.

There is a binary tree of n nodes with distinct labels. You are given the preorder and inorder traversals of the tree, and your task is to determine its postorder traversal.

Input

The first input line has an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

After this, there are two lines describing the preorder and inorder traversals of the tree. Both lines consist of n integers.

You can assume that the input corresponds to a binary tree.

Output

Print the postorder traversal of the tree.

Constraints

    1≤n≤105


Example

Input:
5
5 3 2 1 4
3 5 1 2 4

Output:
3 1 4 2 5
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e5+5;

int N, timer, A[maxN], B[maxN], C[maxN], idx[maxN];
int L[maxN], R[maxN];

int solve(int l1 = 0, int r1 = N-1, int l2 = 0, int r2 = N-1){
    if(l1 > r1 || l2 > r2)  return 0;
    int root = A[l1];
    int m2 = idx[root];
    int len = m2-l2;
    L[root] = solve(l1+1, l1+len, l2, m2-1);
    R[root] = solve(l1+len+1, r1, m2+1, r2);
    return root;
}

void dfs(int u){
    if(L[u])    dfs(L[u]);
    if(R[u])    dfs(R[u]);
    C[timer++] = u;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++)  scanf("%d", &A[i]);
    for(int i = 0; i < N; i++){
        scanf("%d", &B[i]);
        idx[B[i]] = i;
    }

    int root = solve();
    dfs(root);
    for(int i = 0; i < N; i++)
        printf("%d%c", C[i], (" \n")[i==N-1]);
}