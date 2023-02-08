/*
A game consists of n rooms and m teleporters. At the beginning of each day, you start in room 1 and you have to reach room n.

You can use each teleporter at most once during the game. How many days can you play if you choose your routes optimally?

Input

The first input line has two integers n and m: the number of rooms and teleporters. The rooms are numbered 1,2,…,n.

After this, there are m lines describing the teleporters. Each line has two integers a and b: there is a teleporter from room a to room b.

There are no two teleporters whose starting and ending room are the same.

Output

First print an integer k: the maximum number of days you can play the game. Then, print k route descriptions according to the example. You can print any valid solution.

Constraints

    2≤n≤500


1≤m≤1000

1≤a,b≤n


Example

Input:
6 7
1 2
1 3
2 6
3 4
3 5
4 6
5 6

Output:
2
3
1 2 6
4
1 3 4 6

*/
/*
Problem Name: Distinct Routes
Problem Link: https://cses.fi/problemset/task/1711
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
#define tiii tuple<int,int,int,int>
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

vc<tiii> adj[505];
int vis[505];
int n;
int dfs(int s, int f){
    if (s==n) return f;
    vis[s] = 1;
    for (auto &[i,w,j,m]: adj[s]){
        if (w>0 && !vis[i]){
            int b = dfs(i,1);
            if (b>0){
                w-=b;
                get<1>(adj[i][j])+=b;
                return b;
            }
        }
    }
    return 0;
}
void solve(){
    int m; see(n,m);
    while(m--){
        int x,y; see(x,y);
        int j1 = adj[y].sz;
        int j2 = adj[x].sz;
        adj[x].pb({y,1,j1,m+1});
        adj[y].pb({x,0,j2,-m-1});
    }
    int ans=0;
    while(1){
        memset(vis,0,sizeof vis);
        int f = dfs(1,1);
        ans += f;
        if (!f) break;
    }
    putl(ans);
    bool vis[1005]={0};
    rep(i,0,ans){
        vi v={1};
        int x = 1;
        while(x!=n){
            for (auto [i,w,j,m]: adj[x]){
                if (w==0 && m>0 && !vis[m]){
                    v.pb(i); x = i; vis[m]=1;
                    break;
                }
            }
        }
        putl(v.sz);
        for (auto i: v) put(i);L;
    }
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