/*
There is a 2×n grid whose each cell contains some number of coins. The total number of coins is 2n.

Your task is to arrange the coins so that each cell contains exactly one coin. On each move you can choose any coin and move it one step left, right, up or down.

What is the minimum number of moves if you act optimally?

Input

The first input line has an integer n: the width of the grid.

After this, there are two lines that describe the grid. Each line has n integers: the number of coins in each cell.

Output

Print one integer: the minimum number of moves.

Constraints

    1≤n≤105


Example

Input:
4
0 1 0 1
2 0 1 3

Output:
5
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 1e5;

int N, a[2][maxN];

int main(){
    scanf("%d", &N);
    for(int r = 0; r < 2; r++){
        for(int i = 0; i < N; i++){
            scanf("%d", &a[r][i]);
            a[r][i]--;
        }
    }

    ll ans = 0;
    int top = 0, bot = 0;
    for(int i = 0; i < N; i++){
        top += a[0][i];
        bot += a[1][i];

        if((top < 0 && bot > 0) || (top > 0 && bot < 0)){
            if(abs(top) < abs(bot)){
                ans += abs(top);
                bot += top;
                top = 0;
            } else {
                ans += abs(bot);
                top += bot;
                bot = 0;
            }
        }

        ans += abs(top + bot);
    }
    printf("%lld\n", ans);
}