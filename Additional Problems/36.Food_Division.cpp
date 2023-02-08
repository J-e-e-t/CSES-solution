/*
There are n children around a round table. For each child, you know the amount of food they currently have and the amount of food they want. The total amount of food in the table is correct.

At each step, a child can give one unit of food to his or her neighbour. What is the minimum number of steps needed?

Input

The first input line contains an integer n: the number of children.

The next line has n integers a1,a2,…,an: the current amount of food for each child.

The last line has n integers b1,b2,…,bn: the required amount of food for each child.

Output

Print one integer: the minimum number of steps.

Constraints

    1≤n≤2⋅105


0≤ai,bi≤106


Example

Input:
3
3 5 0
2 4 2

Output:
2

Explanation: Child 1 gives one unit of food to child 3, and child 2 gives one unit of food to child 3. 
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 2e5+1;

int N, A[maxN];

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)  scanf("%d", &A[i]);
    for(int i = 1, b; i <= N; i++){
        scanf("%d", &b);
        A[i] += (A[i-1] - b);
    }
    sort(A+1, A+N+1);

    ll ans = 0;
    for(int i = 1; i <= N; i++)
        ans += abs(A[i] - A[(N+1)/2]);
    printf("%lld\n", ans);
}