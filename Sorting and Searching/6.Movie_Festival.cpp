/*
In a movie festival n movies will be shown. You know the starting and ending time of each movie. What is the maximum number of movies you can watch entirely?

Input

The first input line has an integer n: the number of movies.

After this, there are n lines that describe the movies. Each line has two integers a and b: the starting and ending times of a movie.

Output

Print one integer: the maximum number of movies.

Constraints

    1≤n≤2⋅105


1≤a<b≤109


Example

Input:
3
3 5
4 9
5 8

Output:
2
*/

#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
// #define int long long
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
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define INF 1e18
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define by(T, x) [](const T &a, const T &b) { return a.x < b.x; }
 
#ifndef ONLINE_JUDGE
#define debug(x)       \
    cerr << #x << " "; \
    _print(x);         \
    cerr << endl;
#else
#define debug(x)
#endif
 
void _print(ll t)
{
    cerr << t;
}
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(ull t) { cerr << t; }
 
template <class T, class V>
void _print(pair<T, V> p);
template <class T>
void _print(vector<T> v);
template <class T>
void _print(set<T> v);
template <class T, class V>
void _print(map<T, V> v);
template <class T>
void _print(multiset<T> v);
template <class T, class V>
void _print(pair<T, V> p)
{
    cerr << "{";
    _print(p.ff);
    cerr << ",";
    _print(p.ss);
    cerr << "}";
}
template <class T>
void _print(vector<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(set<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(multiset<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T, class V>
void _print(map<T, V> v)
{
    cerr << "[ ";
    for (auto i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
 
const int MOD1 = 2e9 + 7;
const int mod = 1e9 + 7;
const int MOD2 = 998244353;
 
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
 
ll startx, starty;
ll endx, endy;
 
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
 
bool valid(ll x, ll y, ll n, ll m)
{
    if (x >= 0 || y >= 0 || x < n || y < m)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
void dfs(ll node, vector<ll> &vis, ll comp, vector<vector<ll>> &graph, vector<ll> &nodes)
{
    nodes[node] = comp;
    vis[node] = 1;
 
    // cout<<"node "<<node<<" comp "<<comp<<endl;
 
    for (auto edge : graph[node])
    {
        if (vis[edge] == 0)
        {
            dfs(edge, vis, comp, graph, nodes);
        }
    }
 
    return;
}
 
ll power(ll a, ll b)
{
    if (b == 0)
    {
        return 1;
    }
    ll m = power(a, b / 2);
 
    if (b & 1)
    {
        return ((m % mod) * (m % mod) * (a % mod)) % mod;
    }
    else
    {
        return ((m % mod) * (m % mod)) % mod;
    }
 
    return 1;
}
 
ll fun(vector<pair<ll,ll>> &ar,ll end){
 
    ll left = 0;
    ll right = ar.size()-1;
    
 
    ll index =-1;
 
    while(left<=right){
        ll mid = (left+right)/2;
        if(ar[mid].first <= end){
            index = mid;
            left = mid+1;
        }else if(ar[mid].first > end){
            right = mid-1;
        }
    }
 
    return index;
}
 
bool comp(pair<ll,ll> &a, pair<ll,ll> &b){
    if(a.second<b.second){
        return true;
    }else if(a.second==b.second){
        return a.first<b.first;
    }else return false;
}
 
void solve()
{
   ll n,a,b;
   cin>>n;
 
   vector<pair<ll,ll>> ar(n);
 
 
   for(int i=0;i<n;i++){
        cin>>a>>b;
        ar[i]= {a,b};
   }
 
   sort(ar.begin(),ar.end(),comp);
 
   ll lastFinishTime =-1;
   ll ans = 0;
 
   for(int i=0;i<n;i++){
        if(ar[i].first>=lastFinishTime){
            ans++;
            lastFinishTime =ar[i].second;
        }
   }
 
   cout<<ans<<endl;
 
 
    
}
 
signed main()
{
    // init();
    // int t = 1;
    // cin>>t;
 
    // while(t-- > 0){
    solve();
    // }
}