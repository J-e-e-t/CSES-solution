/*
There are n cities and m roads between them. Unfortunately, the condition of the roads is so poor that they cannot be used. Your task is to repair some of the roads so that there will be a decent route between any two cities.

For each road, you know its reparation cost, and you should find a solution where the total cost is as small as possible.

Input

The first input line has two integers n and m: the number of cities and roads. The cities are numbered 1,2,…,n.

Then, there are m lines describing the roads. Each line has three integers a, b and c: there is a road between cities a and b, and its reparation cost is c. All roads are two-way roads.

Every road is between two different cities, and there is at most one road between two cities.

Output

Print one integer: the minimum total reparation cost. However, if there are no solutions, print "IMPOSSIBLE".

Constraints

    1≤n≤105


1≤m≤2⋅105

1≤a,b≤n

1≤c≤109


Example

Input:
5 6
1 2 3
2 3 5
2 4 2
3 4 8
5 1 7
5 4 4

Output:
14
*/

/*
Notice that the road that allows for a "decent route between any two cities,"
with cost "as small as possible" is the definition of a minimum spanning tree.
Thus, we can use our favorite minimum spanning tree algorithm to determine the
cost of such a tree by calculating $\sum c$ for all edges included in the tree.

However, we must also account for the impossible case, which occurs when any
nodes cannot be connected to the tree. Recall that the minimum spanning tree
must contain a total of $n-1$ edges, so we can use a variable $cnt$ that is
incremented every time we add an edge to the minimum spanning tree. After
running Kruskal's, if $cnt \ne n-1$, then we know that we failed to built the
tree properly. Furthermore, since our minimum spanning tree algorithm gurantees
no edges are counted twice, we cannot "accidentally" count $n-1$ edges.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;

#define trav(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define mp make_pair
#define f first
#define s second

struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	// get representive component, uses path compression
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

int cnt=0;
template<class T> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N+1); // edges that unite are in MST
	trav(a,ed)
	if (D.unite(a.s.f,a.s.s)) {
		ans += a.f;
		cnt++;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m; cin >> n >> m;
	vector<pair<ll,pi>> edge;
	for (int i = 0; i < m; i++){
		int a, b; ll c;
		cin >> a >> b >> c;
		edge.push_back(mp(c, mp(a, b)));
	}
	ll ans = kruskal(n, edge);
	if(cnt == n-1){
		cout << ans;
	}
	else{
		cout << "IMPOSSIBLE";
	}
	return 0;
}