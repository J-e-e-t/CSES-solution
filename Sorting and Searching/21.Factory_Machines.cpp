/*
     Time limit: 1.00 s Memory limit: 512 MB 

A factory has n machines which can be used to make products. Your goal is to make a total of t products.

For each machine, you know the number of seconds it needs to make a single product. The machines can work simultaneously, and you can freely decide their schedule.

What is the shortest time needed to make t products?

Input

The first input line has two integers n and t: the number of machines and products.

The next line has n integers k1,k2,…,kn: the time needed to make a product using each machine.

Output

Print one integer: the minimum time needed to make t products.

Constraints

    1≤n≤2⋅105


1≤t≤109

1≤ki≤109


Example

Input:
3 7
3 2 5

Output:
8

Explanation: Machine 1 makes two products, machine 2 makes four products and machine 3 makes one product*/

/*
In this problem, you're given 
$n$
 machines and asked the minimum time these
machines need to work to create 
$t$
 products such that the 
$i$
-th machine
creates a product in 
$k_i$
 time.*/


 /*
 Binary Search
Observe that the time needed to create at least $x$ products is monotonic. In
other words, if the given machines can create $x$ products in $y_1$ time, then
the same machines can create at least $x$ products in $y_2 > y_1$ time. Using
this property, we can binary search over the answer. Read
this module for more information.

For some value we binary search for, $ans$, we are left with the task of
checking whether we can create $t$ products in $ans$ time. To do this, observe
that it's optimal for every machine to work simultaneously. Then, in $ans$ time,
machine $i$ can create $\lfloor \frac{ans}{k_i} \rfloor$ products.

Overall, the $n$ machines can create
‎‎$\sum_{i=1}^{n} \lfloor \frac{ans}{k_i} \rfloor$ products. If this sum
$\geq t$, then $ans$ is valid*/

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


int main() {
	setIO();
	int n; ll t; cin >> n >> t;
	vector<ll> k(n);
	for (int i = 0; i < n; i++) {
		cin >> k[i];
	}
	ll lo = 0; ll hi = 1e18; ll ans = 0;
	while (lo <= hi) {
		ll mid = (lo + hi) /2;
		ll sum = 0;
		for (int i = 0; i < n; i++) {
			sum += (mid / k[i]);
			if(sum >= t){ //deal with overflow
				break;
			}
		}
		if (sum >= t) {
			ans = mid;
			hi = mid-1;
		} else {
			lo = mid+1;
		}
	}
	cout << ans << "\n";
}