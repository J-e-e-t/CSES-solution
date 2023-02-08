
/*
Consider a money system consisting of n coins. Each coin has a positive integer value. Your task is to calculate the number of distinct ordered ways you can produce a money sum x using the available coins.

For example, if the coins are {2,3,5} and the desired sum is 9, there are 3 ways:

    2+2+5


3+3+3

2+2+2+3


Input

The first input line has two integers n and x: the number of coins and the desired sum of money.

The second line has n distinct integers c1,c2,…,cn: the value of each coin.

Output

Print one integer: the number of ways modulo 109+7.

Constraints

    1≤n≤100


1≤x≤106

1≤ci≤106


Example

Input:
3 9
2 3 5

Output:
3
*/


/*The key difference between this problem and
Coin Combinations I is that we're now
trying to find the number of ordered ways to add the coins to $x$. This
means that if we had coins $\{1, 3, 5\}$ and $x=4$, adding $1 + 3$ is treated as
the same "way" as $3 + 1$.
*/

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using vi = vector<int>;

#define pb push_back

#define rsz resize

#define all(x) begin(x), end(x)

#define sz(x) (int)(x).size()

using pi = pair<int,int>;

#define f first

#define s second

#define mp make_pair

void setIO(string name = "") { // name is nonempty for USACO file I/O

	ios_base::sync_with_stdio(0); cin.tie(0); // see Fast Input & Output

	if(sz(name)){

		freopen((name+".in").c_str(), "r", stdin); // see Input & Output

		freopen((name+".out").c_str(), "w", stdout);

	}

}


ll dp[1000001];


const int MOD = (int) 1e9 + 7;


int main(){

	int n, x; cin >> n >> x;

	vi coins(n);

	for (int i = 0; i < n; i++) {

		cin >> coins[i];

	}

	dp[0] = 1;

	for (int i = 1; i <= n; i++) {

		for (int weight = 0; weight <= x; weight++) {

			if(weight - coins[i - 1] >= 0) {  // prevent out of bounds cases

				dp[weight] += dp[weight - coins[i - 1]];

				dp[weight] %= MOD;

			}

		}

	}

	cout << dp[x] << '\n';

}
