/*
There are n applicants and m free apartments. Your task is to distribute the apartments so that as many applicants as possible will get an apartment.

Each applicant has a desired apartment size, and they will accept any apartment whose size is close enough to the desired size.

Input

The first input line has three integers n, m, and k: the number of applicants, the number of apartments, and the maximum allowed difference.

The next line contains n integers a1,a2,…,an: the desired apartment size of each applicant. If the desired size of an applicant is x, he or she will accept any apartment whose size is between x−k and x+k.

The last line contains m integers b1,b2,…,bm: the size of each apartment.

Output

Print one integer: the number of applicants who will get an apartment.

Constraints

    1≤n,m≤2⋅105


0≤k≤109

1≤ai,bi≤109


Example

Input:
4 3 5
60 45 80 60
30 60 75

Output:
2
*/

/*
We can use a greedy approach to solve this problem. First, sort the applicants
and apartments. We can keep two pointers $i$ and $j$ (initialized to 0),
which keep track of the current index of the applicant and apartment we are
looking at respectively. Then, while there are more applicants and apartments to
look through, we repeatedly run the following check:

If $|\texttt{applicants}[i] - \texttt{apartments}[j]| \leq k$, we have found a
suitable apartment for the current applicant. Thus, we increment $i$, $j$, and
our answer.
Otherwise, $\texttt{apartments}[j]$ is either too big or too small for
$\texttt{applicants}[i]$. We can increment $i$ or $j$ accordingly.

Implementation

Time Complexity: $\mathcal{O}(n\log(n)+m\log(m))$*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5;

/*	
 * Variables used for the current problem
 * n: number of applicants
 * m: number of apartments
 * k: max diff between desired and actual size
 * a and b: arrays for applicants and apartments respectively
 */
int n, m, k, a[MAX_N], b[MAX_N], ans;

void solve() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];
	sort(a, a + n);
	sort(b, b + m);
	int i = 0, j = 0;
	while (i < n && j < m){
		// Found a suitable apartment for the applicant
		if (abs(a[i] - b[j]) <= k){
			++i; ++j;
			++ans;
		}
		else{
			// If the desired apartment size of the applicant is too big,
			// move the apartment pointer to the right to find a bigger one
			if (a[i] - b[j] > k){
				++j;
			}
			// If the desired apartment size is too small,
			// skip that applicant and move to the next person
			else{
				++i;
			}
		}
	}
	cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}