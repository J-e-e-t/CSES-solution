/*
Forest Queries

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

You are given an n×n
grid representing the map of a forest. Each square is either empty or contains a tree. The upper-left square has coordinates (1,1), and the lower-right square has coordinates (n,n).

Your task is to process q queries of the form: how many trees are inside a given rectangle in the forest?

Input

The first input line has two integers n and q: the size of the forest and the number of queries.

Then, there are n lines describing the forest. Each line has n characters: . is an empty square and * is a tree.

Finally, there are q lines describing the queries. Each line has four integers y1, x1, y2, x2 corresponding to the corners of a rectangle.

Output

Print the number of trees inside each rectangle.

Constraints

    1≤n≤1000


1≤q≤2⋅105

1≤y1≤y2≤n

1≤x1≤x2≤n


Example

Input:
4 3
.*..
*.**
**..
****
2 2 3 4
3 1 3 1
1 1 2 2

Output:
3
1
2

*/

/*
For every query of the form (x1,y1,x2,y2) we need to answer the number of trees inside the rectangle described by the top left cell of rectangle (x1,y1) and the bottom right cell of rectangle (x2,y2).

Define : DP[i][j] as the number of trees in the rectangle described by (1,1) and (i,j).

Can we use DP matrix to evaluate answers for every query?

YES.

But how?

first please check this image : https://www.techiedelight.com/wp-content/uploads/Result.png
Trees in rectangle ((x1,y1),(x2,y2)) can be decomposed into the following rectangles :
1. Trees in rectangle ((1,1),(x2,y2)) = DP[x2][y2]
2. Trees in rectangle ((1,1),(x1-1,y2)) = DP[x1-1][y2]
3. Trees in rectangle ((1,1),(x2,y1-1)) = DP[x2][y1-1]
4. Trees in rectangle ((1,1),(x1-1,y1-1)) = DP[x1-1][y1-1]

Finally we have the answer to our query as DP[x2][y2] — DP[x1-1][y2] — DP[x2][y1-1] + DP[x1-1][y1-1]

How to build DP matrix?
Let tree[i][j] = 1, if there is a tree at cell (i,j) else tree[i][j] = 0.

 DP[0][0] = DP[-1][0] = DP[0][-1] = 0
 for i from 1 to N:
    for j from 1 to N:
     DP[i][j] = DP[i-1][j] + DP[i][j-1] — DP[i-1][j-1] + tree[i][j] 

Time complexity for build O(N*N) and time complexity per query is O(1).
*/


/*
    author: kartik8800
*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(ll i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;

bool grid[1001][1001];
int dp[1001][1001];

void build_dp(int n, int m)
{
    dp[0][0] = dp[1][0] = dp[0][1] = 0;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            dp[i][j] = grid[i][j] + dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
    }
}

int getDP(int x, int y)
{
    return dp[x][y];
}

int query(int x1, int y1, int x2, int y2)
{
    return getDP(x2,y2) - getDP(x2,y1-1) - getDP(x1-1,y2) + getDP(x1-1,y1-1);
}

int main() {
   fast_io;
   int n,q;
   cin >> n >> q;

   for(int i = 1; i <= n; i++)
   {
       for(int j = 1; j <= n; j++)
       {
           char ch;
           cin >> ch;
           if(ch == '*')
                grid[i][j] = 1;
           else grid[i][j] = 0;
       }
   }

   build_dp(n,n);

   while(q--)
   {
            int x1,x2,y1,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x1,y1,x2,y2) << '\n';
   }
   return 0;
}
