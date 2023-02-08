/*
You have n coins with positive integer values. What is the smallest sum you cannot create using a subset of the coins?

Input

The first input line has an integer n: the number of coins.

The second line has n integers x1,x2,…,xn: the value of each coin.

Output

Print one integer: the smallest coin sum.

Constraints

    1≤n≤2⋅105


1≤xi≤109


Example

Input:
5
2 9 1 2 7

Output:
6
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
 
int fun(int num){
    ll sum = 0;
    ll mul = 1;
    
    
 
    while(true){
        sum+= num/mul;
        mul*=10;
 
        if(mul>num){
            break;
        }
    }
 
    return sum;
 
 
}
    
int dp[200006][32] = {0};
 
int main()
{
	// init();
	int t = 1;
	// cin>>t;
 
    
 
 
	while(t-- > 0){
       ll n;
       cin>>n;
 
       vector<ll> ar(n);
       for(int i=0;i<n;i++){
        cin>>ar[i];
       }
 
       sort(ar.begin(),ar.end());
    //    if(ar[0]!=1){
    //         cout<<1<<endl;
    //          break;
    //    }
 
       long long sum = 0;
       for(int i=0;i<n;i++){
            if(sum+1<ar[i]){
                break;
            }
            sum+=ar[i];
       }
       cout<<sum+1<<endl;
 
	}
 
 
	   
}