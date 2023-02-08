/*
List A consists of n positive integers, and list B contains the sum of each element pair of list A.

For example, if A=[1,2,3], then B=[3,4,5], and if A=[1,3,3,3], then B=[4,4,4,6,6,6].

Given list B, your task is to reconstruct list A.

Input

The first input line has an integer n: the size of list A.

The next line has n(n−1)2 integers: the contents of list B.

You can assume that there is a list A that corresponds to the input, and each value in A is between 1…k.

Output

Print n integers: the contents of list A.

You can print the values in any order. If there are more than one solution, you can print any of them.

Constraints

    3≤n≤100


1≤k≤109


Example

Input:
4
4 4 4 6 6 6

Output:
1 3 3 3

Explanation: In this case list A can be either [1,3,3,3] or [2,2,2,4] and both solutions are accepted. 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 101, maxM = 4951;

int N, M;
multiset<ll> Bvals;
ll A[maxN], B[maxM];

bool check(ll a0){
    A[0] = a0;
    Bvals.clear();
    for(int i = 0; i < M; i++)
        Bvals.insert(B[i]);

    for(int i = 1; i < N; i++){
        for(int j = 0; j < i-1; j++){
            if(Bvals.find(A[j]+A[i-1]) == Bvals.end())
                return false;
            Bvals.erase(Bvals.lower_bound(A[j]+A[i-1]));
        }
        A[i] = *Bvals.begin() - A[0];
    }

    // Confirm that the last element, A[N-1], works. We desire
    // the sum with the other A[i] to produce the remaining Bvals
    for(int j = 0; j < N-1; j++){
        if(Bvals.find(A[j]+A[N-1]) == Bvals.end())
            return false;
        Bvals.erase(Bvals.lower_bound(A[j]+A[N-1]));
    }

    return true;
}

int main(){
    scanf("%d", &N);
    M = N*(N-1)/2;
    for(int i = 0; i < M; i++)
        scanf("%lld", &B[i]);
    sort(B, B+M);

    for(int i = 1; i < M; i++){
        ll a0 = (B[0] + B[1] - B[i])/2;
        if(1 <= a0 && a0 <= B[0]/2 && check(a0)){
            for(int j = 0; j < N; j++)
                printf("%lld%c", A[j], (" \n")[j==N-1]);
            return 0;
        }
    }

    printf("IMPOSSIBLE\n");
}