/*
Your task is to efficiently calculate values a^b modulo 109+7.

Note that in this task we assume that 0^0=1.

Input

The first input line contains an integer n: the number of calculations.

After this, there are n lines, each containing two integers a and b.

Output

Print each value ab modulo 1e9+7.

Constraints

    1≤n≤2⋅1e5


0≤a,b≤1e9


Example

Input:
3
3 4
2 8
123 123

Output:
81
256
921450052*/


#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define lld long double
#define endl "\n"
#define ff first
#define ss second
#define MOD1 1000000007
#define MOD2 998244353
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
 
ll poww(int a,int b)
{
    ll x;
    if(b==0)
    {
        return 1;
    }
    if(b==1)
    {
        return a;
    }
    else
    {
        x=poww(a,b/2)%MOD1;
        x=(x*x)%MOD1;
        if(b&1)
        {
            return (a*x)%MOD1;
        }
        else{
            return x%MOD1;
        }
    }
}
 
signed main()
{
	init();
	int t;
	cin >> t;
	while (t--)
	{
        int a,b;
        cin>>a>>b;
 
        cout<<poww(a,b)<<endl;
	}
}