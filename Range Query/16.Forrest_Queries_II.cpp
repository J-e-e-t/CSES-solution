/*
Problem is almost the same as Forest Queries but we also have point updates.
I will discuss two approaches, one of them is quite efficient while the other one struggles to run in the time limit(passes if constant factor is low).

Approach 1

Let us do build the same DP matrix which we had built for the problem Forest Queries. If somehow we are able to keep our DP matrix consistent with the updates then our answer will be the same as before.

ANSWER TO QUERY (x1,y1,x2,y2) : DP[x2][y2] — DP[x1-1][y2] — DP[x2][y1-1] + DP[x1-1][y1-1]

How to efficiently track the updates that happen on some entry DP[i][j]?
Which entries of the DP matrix change if cell (i,j) is updated?

DP[x][y] represents the number of trees in the rectangle described by ((1,1),(x,y)).
Only those entries will be affected which contain the cell (i,j). If the rectangle described by ((1,1),(x,y)) contains the cell (i,j) then we have the following conclusions about x and y :
1. x >= i
2. y >= j

What will be the change in these entries?
Either a +1 or a -1, depending upon whether a tree was planted or removed in cell (i,j).

Alright, so now I need to efficiently add or subtract 1 from all the matrix entries (x,y) where that x >= i and y >= j.
So how do we track these updates?

Range query Data structures.
We needed to either add or subtract 1 from all entries (x,y).
Now consider the row X(X >= x) : for this row we need to update entries (X,j), (X, j+1) ... (X,N)
This is nothing but a range update to the range [j,N].
So here is what we can do, keep a fenwick tree for each row. Fenwick[k] represents the fenwick tree for the kth row and Fenwick[k].rangeSum(0,j) represents the net change for the entry (k,j).

For updates, simply do the point updates Fenwick[k].update(j, delta) for all k from i to N where delta is either 1 or -1.

Time complexity O(Q*N*logN)
AC code : https://ideone.com/mcAdwL
Code for fenwick tree is taken from : https://cp-algorithms.com/data_structures/fenwick.html
*/

/*
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

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

int sum(int x, int y){return x + y;}

bool grid[1001][1001];
int dp[1001][1001];
vector<FenwickTree> row_updates(1001, FenwickTree(1001));

void build_dp(int n, int m)
{
    dp[0][0] = dp[1][0] = dp[0][1] = 0;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            dp[i][j] = grid[i][j] + dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
    }
}

void update(int i, int j, int n)
{
    int delta = -1;
    if(grid[i][j] == 0) // it was empty
        delta = 1; // now it has a tree

    grid[i][j] = !grid[i][j]; // switch the state
    for(int k = i; k <= n; k++)
        row_updates[k].add(j, delta);
}

int getDP(int x, int y)
{
    return dp[x][y] + row_updates[x].sum(y);
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
        int t;
        cin >> t;
        if(t == 1)
        {
            int x,y;
            cin >> x >> y;
            update(x,y,n);
        }
        else
        {
            int x1,x2,y1,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x1,y1,x2,y2) << '\n';
        }
   }
   return 0;
}
*/

/*
 Approach 2
This approach is more efficient and some might also find it easier to understand.
It uses a 2D Binary Indexed tree to achieve an overall time complexity of O(N^2 + Q*log^2(N)).

You can read more about it here : https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/#2d


Essentially, we just nest the loops that one would find in a 1D BIT to get N-dimensional BITs. We can then use PIE to query subrectangles.
*/
#include <bits/stdc++.h>

using namespace std;


int bit[1001][1001];

int n;


void update(int x, int y, int val) {

	for (; x <= n; x += (x & (-x))) {

		for (int i = y; i <= n; i += (i & (-i))) {

			bit[x][i] += val;

		}

	}

}


int query(int x1, int y1, int x2, int y2) {

	int ans = 0;

	for (int i = x2; i; i -= (i & (-i))) {

		for (int j = y2; j; j -= (j & (-j))) {

			ans += bit[i][j];

		}

	}

	for (int i = x2; i; i -= (i & (-i))) {

		for (int j = y1 - 1; j; j -= (j & (-j))) {

			ans -= bit[i][j];

		}

	}

	for (int i = x1 - 1; i; i -= (i & (-i))) {

		for (int j = y2; j; j -= (j & (-j))) {

			ans -= bit[i][j];

		}

	}

	for (int i = x1 - 1; i; i -= (i & (-i))) {

		for (int j = y1 - 1; j; j -= (j & (-j))) {

			ans += bit[i][j];

		}

	}

	return ans;

}


int main() {

	iostream::sync_with_stdio(false);

	cin.tie(0);

	int q;

	cin >> n >> q;

	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {

		char c;

		cin >> c;

		if (c == '*') update(j, i, 1);

	}

	while (q--) {

		int t;

		cin >> t;

		if (t == 1) {

			int x, y;

			cin >> y >> x;

			if (query(x, y, x, y)) update(x, y, -1);

			else update(x, y, 1);

		} else {

			int y1, x1, y2, x2;

			cin >> y1 >> x1 >> y2 >> x2;

			cout << query(x1, y1, x2, y2) << '\n';

		}

	}

	return 0;

}
