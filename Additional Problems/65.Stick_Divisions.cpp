/*
You have a stick of length x and you want to divide it into n sticks, with given lengths, whose total length is x.

On each move you can take any stick and divide it into two sticks. The cost of such an operation is the length of the original stick.

What is the minimum cost needed to create the sticks?

Input

The first input line has two integers x and n: the length of the stick and the number of sticks in the division.

The second line has n integers d1,d2,…,dn: the length of each stick in the division.


Output

Print one integer: the minimum cost of the division.

Constraints

    1≤x≤109


1≤n≤2⋅105

∑di=x


Example

Input:
8 3
2 3 3

Output:
13

Explanation: You first divide the stick of length 8 into sticks of length 3 and 5 (cost 8). After this, you divide the stick of length 5 into sticks of length 2 and 3 (cost 5). The total cost is 8+5=13. */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, x, d;
ll sum;
priority_queue<int, vector<int>, greater<int>> sticks;

int main(){
    scanf("%d %d", &x, &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &d);
        sticks.push(d);
    }
    while(sticks.size() > 1){
        int a = sticks.top(); sticks.pop();
        int b = sticks.top(); sticks.pop();
        sticks.push(a+b);
        sum += a + b;
    }
    printf("%lld\n", sum);
}
