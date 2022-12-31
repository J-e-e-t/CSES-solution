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



const int MOD=1000000007;
long long int inverse(long long int i){
    //https://cp-algorithms.com/algebra/module-inverse.html
    if(i==1) return 1;
    return (MOD - ((MOD/i)*inverse(MOD%i))%MOD+MOD)%MOD;
}


ll POW(ll a,ll b)
{
    if(b==0) return 1;
    if(b==1) return a%MOD;
    ll temp=POW(a,b/2);
    if(b%2==0) return (temp*temp)%MOD;
    else return (((temp*temp)%MOD)*a)%MOD;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll fact[1000001];
    fact[0]=1;
    fact[1]=1;
    for(int i=2;i<=1000000;i++)
    {
        fact[i]=(fact[i-1]*i)%MOD;
    }
    string s;
    cin>>s;
    ll n=s.size();
    ll cnt[26]={};
    for(int i=0;i<n;i++)
    {
        cnt[s[i]-'a']++;
    }
    ll tot=fact[n];
    for(int i=0;i<26;i++)
    {
        tot*=inverse(fact[cnt[i]]);
        tot%=MOD;
    }
    cout<<tot;
}



