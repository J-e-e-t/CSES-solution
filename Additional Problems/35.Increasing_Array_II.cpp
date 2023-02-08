/*
You are given an array of n integers. You want to modify the array so that it is increasing, i.e., every element is at least as large as the previous element.

On each move, you can increase or decrease the value of any element by one. What is the minimum number of moves required?

Input

The first input line contains an integer n: the size of the array.

Then, the second line contains n integers x1,x2,…,xn: the contents of the array.

Output

Print the minimum number of moves.

Constraints

    1≤n≤2⋅105


1≤xi≤109


Example

Input:
5
3 8 5 6 5

Output:
4
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, x;
priority_queue<int> Q;

int main(){
    scanf("%d", &N);
    ll ans = 0;
    for(int i = 0; i < N; i++){
        scanf("%d", &x);
        Q.push(x);
        ans += Q.top() - x;
        Q.pop();
        Q.push(x);
    }
    printf("%lld\n", ans);
}