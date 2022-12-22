/*
You are playing a game consisting of n planets. Each planet has a teleporter to another planet (or the planet itself).

Your task is to process q queries of the form: when you begin on planet x and travel through k teleporters, which planet will you reach?

Input

The first input line has two integers n and q: the number of planets and queries. The planets are numbered 1,2,…,n.

The second line has n integers t1,t2,…,tn: for each planet, the destination of the teleporter. It is possible that ti=i.

Finally, there are q lines describing the queries. Each line has two integers x and k: you start on planet x and travel through k teleporters.

Output

Print the answer to each query.

Constraints

    1≤n,q≤2⋅105


1≤ti≤n

1≤x≤n

0≤k≤109


Example

Input:
4 3
2 1 1 4
1 2
3 4
4 1

Output:
1
2
4
*/

/*
Construct a parent matrix (where $\texttt{parent}[i][d]$ is the $2^d$th parent
of $i$). Then, we can answer each query by using
binary jumping from the starting node based on the binary
representation of the distance.

Since the query distances can be up to $10^9$, we set the maximum depth to
$\lceil{\log_2{10^9}}\rceil = 30$.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;
const int MAXD = 30; // ceil(log2(10^9))

// number of planets and queries
int n, q;
// parent matrix where [i][j] corresponds to i's (2^j)th parent
int parent[MAXN][MAXD];

int jump(int a, int d) {
	for(int i=0; i<MAXD; i++) if(d & (1<<i))
		a = parent[a][i];
	return a;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;
	for(int i=1; i<=n; i++) {
		cin >> parent[i][0];
	}
	// evaluate the parent matrix
	for(int d=1; d<MAXD; d++)
	for(int i=1; i<=n; i++) {
		parent[i][d] = parent[parent[i][d-1]][d-1];
	}

    // for(int i=1;i<=n;i++){
    //     for(int d=0;d<MAXD;d++){
    //         cout<<parent[i][d]<<" ";
    //     }
    //     cout<<endl;
    // }
	// process queries
	while(q--) {
		int a, d;
		cin >> a >> d;
		cout << jump(a, d) << '\n';
	}
}

