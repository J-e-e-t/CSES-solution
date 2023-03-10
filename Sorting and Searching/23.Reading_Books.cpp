
/*
There are n books, and Kotivalo and Justiina are going to read them all. For each book, you know the time it takes to read it.

They both read each book from beginning to end, and they cannot read a book at the same time. What is the minimum total time required?

Input

The first input line has an integer n: the number of books.

The second line has n integers t1,t2,…,tn: the time required to read each book.

Output

Print one integer: the minimum total time.

Constraints

    1≤n≤2⋅105


1≤ti≤109


Example

Input:
3
2 8 3

Output:
16
*/
/*
Problem Name: Reading Books
Problem Link: https://cses.fi/problemset/task/1631
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
const ll inf = INT_MAX;
const ld ep = 0.0000001;
const ld pi = acos(-1.0);
const ll md = 1000000007;
 
void solve(){
    int n; see(n);
    //assume all durations to be sticks of given length
    //arrange first row in ascending order
    //now for second row- put biggest stick at first then put remaining in asceding order
    //cases: if 2*(biggest length) > sum then overlap occurs between the two big sticks 
    //otherwise no overlap occurs 
    //e.g 1 2 2
    //row 1: -++==
    //row 2: ==-++ no overlap occurs
    //e.g 1 2 4
    //row 1: -++====
    //row 2: ====  overlap occurs
    //correction- row 1: -++ ====
    //correction- row 2: ====-++
    int s=0,mx=0;
    rep(i,0,n){
        int x; see(x);
        mx = max(mx,x); s+=x;
    }
    put( max(2*mx,s));
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
    #ifndef ONLINE_JUDGE
    clock_t tStart = clock();
    cerr<<fixed<<setprecision(10)<<"\nTime Taken: "<<(double)(clock()- tStart)/CLOCKS_PER_SEC<<endl;
    #endif
}
