/*
Uolevi has won a contest, and the prize is a free flight trip that can consist of one or more flights through cities. Of course, Uolevi wants to choose a trip that has as many cities as possible.

Uolevi wants to fly from Syrjälä to Lehmälä so that he visits the maximum number of cities. You are given the list of possible flights, and you know that there are no directed cycles in the flight network.

Input

The first input line has two integers n and m: the number of cities and flights. The cities are numbered 1,2,…,n. City 1 is Syrjälä, and city n is Lehmälä.

After this, there are m lines describing the flights. Each line has two integers a and b: there is a flight from city a to city b. Each flight is a one-way flight.

Output

First print the maximum number of cities on the route. After this, print the cities in the order they will be visited. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

Constraints

    2≤n≤105


1≤m≤2⋅105

1≤a,b≤n


Example

Input:
5 5
1 2
2 5
1 3
3 4
4 5

Output:
4
1 3 4 5
*/
/*
Problem Name: Longest Flight Route
Problem Link: https://cses.fi/problemset/task/1680
Author: Sachin Srivastava (mrsac7)
*/
#include<bits/stdc++.h>
using namespace std;
template<typename... T>
void see(T&... args) { ((cin >> args), ...);}
template<typename... T>
void put(T&&... args) { ((cout << args << " "), ...);}
template<typename... T>
void putl(T&&... args) { ((cout << args << " "), ...); cout<<'\n';}
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {cerr << *it << "=" << a << ", "; err(++it, args...);}
#define int long long
#define pb push_back
#define F first
#define S second
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define tiii tuple<int,int,int>
#define vi vector<int>
#define vii vector<pii>
#define vc vector
#define L cout<<'\n';
#define E cerr<<'\n';
#define all(x) x.begin(),x.end()
#define rep(i,a,b) for (int i=a; i<b; ++i)
#define rev(i,a,b) for (int i=a; i>b; --i)
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define setpr(x) cout<<setprecision(x)<<fixed
#define sz size()
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define sees(s,n) for(int i=0;i<n;i++){int x; cin>>x; s.insert(x);}
const ll inf = 1LL<<62;
const ld ep = 0.0000001;
const ld pi = acos(-1.0);
const ll md = 1000000007;

vi adj[100005];
bool vis[100005];
vi v;
void dfs(int s){
    if (vis[s]) return;
    vis[s]=1;
    for (auto i: adj[s]) dfs(i);
    v.pb(s);
}
void solve(){
    int n,m; see(n,m);
    rep(i,0,m){
        int a,b; see(a,b);
        adj[b].pb(a);
    }
    rep(i,1,n+1){
        if (!vis[i]) dfs(i);
    }
    // for (auto i:v) put(i);
    vi t; int i=0,f=0;
    while(i<v.sz){
        if (f==0){
            if (v[i]==1) {f=1; t.pb(1);}
        }
        else{
            t.pb(v[i]);
        }
        i++;
    }
    int len[100005]={0}, par[100005]={0};
    len[1]=1, par[1]=0;
    for (auto i: t) {
        for (auto j: adj[i]){
            if (len[i]<len[j]+1 && len[j]){
                len[i]=len[j]+1;
                par[i] = j;
            }
        }
    }
    i = n;
    vi v;
    while(i!=0){
        v.pb(i); i = par[i];
    }
    reverse(all(v)); 
    if (v.sz<2) {put("IMPOSSIBLE"); return;}
    putl(v.sz);
    for (auto i: v) put(i);
}    
signed main(){
    IOS;
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int t=1;
    //cin>>t;
    while(t--){
        solve();
        //cout<<'\n';
    }
    #ifdef LOCAL
    clock_t tStart = clock();
    cerr<<fixed<<setprecision(10)<<"\nTime Taken: "<<(double)(clock()- tStart)/CLOCKS_PER_SEC<<endl;
    #endif
}
