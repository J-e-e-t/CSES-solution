/*
You are given a tree consisting of n nodes.

A matching is a set of edges where each node is an endpoint of at most one edge. What is the maximum number of edges in a matching?

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print one integer: the maximum number of pairs.

Constraints

    1≤n≤2⋅105


1≤a,b≤n


Example

Input:
5
1 2
1 3
3 4
3 5

Output:
2

Explanation: One possible matching is (1,2) and (3,4). 
*/

// This problem can be reduced to maximum bipartite matching problem but first we need to split the tree into a bipartite graph. One way to do that is to put all nodes at even depth in the first group and odd ones in the other group. Such a splitting will make sure that we do not have any edges within the same group.

// Next, we can use Hopkraft Karp algorithm to find the maximum matching in the bipartite graph created.
// Code

#include<bits/stdc++.h>
using namespace std;
#define NIL 0
#define INF (1<<28)

const int SZ = 400005;
int x, u, v;
vector<int> adj_inp[SZ];
vector<int> adj[SZ];
int n, m, match[SZ], dist[SZ];
 
bool bfs() {
    int i, u, v, len;
    queue<int> Q;
    for(i=1; i<=n; i++) {
        if(match[i]==NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=NIL) {
            for(int v: adj[u]) {
                if(dist[match[v]]==INF) {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}
 
bool dfs(int u) {
    int i, v, len;
    if(u!=NIL) {
        for(int v: adj[u]) {
            if(dist[match[v]]==dist[u]+1) {
                if(dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}
 
int hopcroft_karp_max_match() {
    int matching = 0, i;
    // match[] is assumed NIL for all vertex in adj
    while(bfs())
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i))
                matching++;
    return matching;
}
 
void make_bipartite_dfs(int u, int p, int l) {
    if(l%2 and p != -1) {
        adj[u].push_back(p+n);
        adj[p+n].push_back(u);
    }
    for(int v: adj_inp[u]) {
        if(v!=p) {
            if(l%2) {
            adj[u].push_back(v+n);
            adj[v+n].push_back(u);
            }
            make_bipartite_dfs(v, u, l+1);
        }
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n-1; i++) {
        cin >> u >> v;
        adj_inp[u].push_back(v);
        adj_inp[v].push_back(u);
    }
    make_bipartite_dfs(1, -1, 1);
    cout << hopcroft_karp_max_match() << endl;
}


/*
Solution 1

In this problem, we're asked to find the maximum matching of a tree, or the
largest set of edges such that no two edges share an endpoint. Let's use DP on
trees to do this.

Root the tree at node $1$, allowing us to define the subtree of each node.

Let $dp_2[v]$ represent the maximum matching of the subtree of $v$ such that we
don't take any edges leading to some child of $v$. Similarly, let $dp_1[v]$
represent the maximum matching of the subtree of $v$ such that we take one edge
leading into a child of $v$. Note that we can't take more than one edge leading
to a child, because then two edges would share an endpoint.


Warning!Loop through the children of $v$ twice to calculate $dp_1[v]$ and $dp_2[v]$
separately! You need to know $dp_2[v]$ to calculate $dp_1[v]$.

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

vi adj[200005]; int dp[200005][2];

void dfs(int v, int p) {
	for (int to : adj[v]) {
		if (to != p) {
			dfs(to, v);
			dp[v][0] += max(dp[to][0], dp[to][1]);
		}
	}
	for (int to : adj[v]) {
		if (to != p) {
			 dp[v][1] = max(dp[v][1], dp[to][0] + 1 + dp[v][0] - max(dp[to][0], dp[to][1]));
		}
	}
}

int main() {
	setIO();
	int n; cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		adj[u].pb(v), adj[v].pb(u);
	}
	dfs(0, -1);
	cout << max(dp[0][0], dp[0][1]) << '\n';
}
*/

/*
Solution 2 - Greedy

Just keep matching a leaf with the only vertex adjacent to it while possible.

int n;
vi adj[MX];
bool done[MX];
int ans = 0;

void dfs(int pre, int cur) {
	for (int i: adj[cur]) {
		if (i != pre) {
			dfs(cur,i);
			if (!done[i] && !done[cur])
				done[cur] = done[i] = 1, ans ++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	F0R(i,n-1) {
		int a,b; cin >> a >> b;
		adj[a].pb(b), adj[b].pb(a);
	}
	dfs(0,1);
	cout << ans;
}*/