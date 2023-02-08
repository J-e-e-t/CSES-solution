/*
Your task is to place eight queens on a chessboard so that no two queens are attacking each other. As an additional challenge, each square is either free or reserved, and you can only place queens on the free squares. However, the reserved squares do not prevent queens from attacking each other.

How many possible ways are there to place the queens?

Input

The input has eight lines, and each of them has eight characters. Each square is either free (.) or reserved (*).

Output

Print one integer: the number of ways you can place the queens.

Example

Input:
........
........
..*.....
........
........
.....**.
...*....
........

Output:
65
*/
/*
By Generating Permutations

Since no two queens can be in the same column, let's generate a permutation of
length $8$. Then, the $p_i$ represents the column that the $i$-th queen goes on.

By generating all permutations, we can quickly test all possible placements, and
count how many are valid.

To make the implementation easier, we can observe that some bottom-left to
top-right diagonal can be represented as all squares $i, j$ such that
$i + j = S$ for some $S$. Similarly, some bottom-right to top-left diagonal can
be represented as $i + 7 - j$ if $i, j$ are zero-indexed.
*/
#include <bits/stdc++.h>

using namespace std;

bool ok[8][8];
int ans = 0;

int main() {
	for (int i = 0; i < 8; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < 8; j++) {
			ok[i][j] = (s[j] == '.');
		}
	}
	vector<int> vals(8);

	iota(vals.begin(), vals.end(), 0);  // set vals to 0 1 ... 7

	do {
		bool works = true;
		bool blocked[16];
		for (int i = 0; i < 8; i++) {
			if (!ok[i][vals[i]]) {
				works = false;
			}
		}
		// first mark all squares as not blocked
		memset(blocked, false, sizeof(blocked));
		for (int i = 0; i < 8; i++) {
			if (blocked[i + vals[i]]) {
				works = false;
			}
			blocked[i + vals[i]] = true;  // mark this diagonal
		}
		memset(blocked, false, sizeof(blocked));
		for (int i = 0; i < 8; i++) {
			if (blocked[i + 7 - vals[i]]) {
				works = false;
			}
			blocked[i + 7 - vals[i]] = true;
		}
		if (works) ++ans;
	} while (next_permutation(vals.begin(), vals.end()));

	cout << ans << '\n';
}

/*
Using Backtracking

According to CPH:

A backtracking algorithm begins with an empty solution and extends the
solution step by step. The search recursively goes through all different ways
how a solution can be constructed.


Since the bounds are small, we can recursively backtrack over all ways to place
the queens, storing the current state of the board.

Then, we can try to place a queen at all squares $x, y$ if it isn't attacked by
a queen or blocked and recurse, before removing this queen and backtracking.

Finally, when we have placed all the queens and the board's state is valid, then
increment the answer.
*/
/*

#include <bits/stdc++.h>

using namespace std;

string g[8];
bool sum[15], diff[15], c[8];
int ans = 0;

void dfs(int r) {  // place queen in r-th row
	if (r == 8) {
		++ans;  // found valid placement
		return;
	}
	for (int i = 0; i < 8; ++i) {
		if (g[r][i] == '.' && !c[i] && !sum[i + r] && !diff[i - r + 7]) {
			c[i] = sum[i + r] = diff[i - r + 7] = true;
			dfs(r + 1);
			c[i] = sum[i + r] = diff[i - r + 7] = false;
		}
	}
}

int main() {
	for (int i = 0; i < 8; ++i) cin >> g[i];
	dfs(0);
	cout << ans;
}
*/