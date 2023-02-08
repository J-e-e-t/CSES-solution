/*
You are in a book shop which sells n different books. You know the price, the number of pages and the number of copies of each book.

You have decided that the total price of your purchases will be at most x. What is the maximum number of pages you can buy? You can buy several copies of the same book.

Input

The first input line contains two integers n and x: the number of book and the maximum total price.

The next line contains n integers h1,h2,…,hn: the price of each book.

The next line contains n integers s1,s2,…,sn: the number of pages of each book.

The last line contains n integers k1,k2,…,kn: the number of copies of each book.


Output

Print one integer: the maximum number of pages.

Constraints

    1≤n≤100


1≤x≤105

1≤hi,si,ki≤1000


Example

Input:
3 10
2 6 3
8 5 4
3 5 2

Output:
28

Explanation: You can buy three copies of book 1 and one copy of book 3. The price is 3⋅2+3=9 and the number of pages is 3⋅8+4=28. */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 100, maxK = 1000, maxX = 1e5+1;

int N, X, h[maxN], s[maxN], k[maxN];
ll dp[maxX];

int main(){
    scanf("%d %d", &N, &X);
    for(int i = 0; i < N; i++)  scanf("%d", &h[i]);
    for(int i = 0; i < N; i++)  scanf("%d", &s[i]);
    for(int i = 0; i < N; i++)  scanf("%d", &k[i]);

    fill(dp+1, dp+X+1, -1);
    for(int i = 0; i < N; i++){
        for(int b = 1; k[i] > 0; b++){
            int amnt = min(b, k[i]);
            k[i] -= b;
            int price = amnt * h[i];
            int pages = amnt * s[i];
            for(int j = X; j >= price; j--)
                if(dp[j-price] != -1)
                    dp[j] = max(dp[j], dp[j-price] + pages);
        }
    }

    for(int i = 1; i <= X; i++)
        dp[i] = max(dp[i], dp[i-1]);
    printf("%lld\n", dp[X]);
}