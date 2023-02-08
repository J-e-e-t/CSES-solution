/*
You are given a tree consisting of n nodes.

The diameter of a tree is the maximum distance between two nodes. Your task is to determine the diameter of the tree.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print one integer: the diameter of the tree.

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
3

Explanation: The diameter corresponds to the path 2→1→3→5. 
*/

#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ull unsigned long long
#define lld long double
#define endl "\n"
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define MAXA(a, n) *max_element(a, a + n)
#define MINA(a, n) *min_element(a, a + n)
#define REV(v) reverse(v.begin(), v.end())
#define SUM(v) accumulate(v.begin(), v.end(), 0)
#define REP(i, a, n) for (ll i = a; i < n; i++)
#define REP1(i, a, n) for (ll i = a; i <= n; i++)
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define INF 1e18
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define min(a, b) (((a)<(b))?(a):(b))
#define max(a, b) (((a)>(b))?(a):(b))
#define by(T, x) [](const T& a, const T& b) { return a.x < b.x; }
 
 
 
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif
 
 
 
void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}
 
 
 
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
 
 
const int MOD1=2e9+7;
const int MOD2=998244353;
const int mod=1e9+7;
 
void init()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#else
#endif
}
 
int dfs(int par,int node,vector<vector<int>> &tree, vector<int> &height,vector<int> &parent){
	if(height[node]!=-1){
		return height[node];
	}
	parent[node] = par;
	
	int mx = 0;
	for(auto ch : tree[node]){
		if(ch==par){
			continue;
		}
		mx = max(mx,dfs(node,ch,tree,height,parent));
	}
 
	height[node] = 1+mx;
	return height[node];
}
void solve(){
	int n,a,b;
	cin>>n;
 
	vector<vector<int>> tree(n+1);
	vector<int> height(n+1,-1);
	vector<int> parent(n+1,-1);
 
	for(int i=0;i<n-1;i++){
		cin>>a>>b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
 
	a = dfs(0,1,tree,height,parent);
 
	// _print(height);
 
	priority_queue<int,vector<int>, greater<int>> pq;
	
 
	int ans = 0;
 
	for(int i=1;i<=n;i++){
		pq.push(0);
		pq.push(0);
		for(auto ch: tree[i]){
			if(ch == parent[i]){
				continue;
			}
			pq.push(height[ch]);
			if(pq.size()>2){
				pq.pop();
			}
		}
 
		int mx1 = pq.top();
		pq.pop();
		int mx2 = pq.top();
		pq.pop();
 
		// cout<<"for node "<<i<<" -> mx1="<<mx1<<" mx2= "<<mx2<<endl; 
 
 
		ans = max(ans, mx1+mx2);
	}
 
	cout<<ans;
 
 
	
}
 
 
int main()
{
	// init();
	int t = 1;
	// cin>>t;
 
 
	while(t-- > 0){
		solve();
	}

}