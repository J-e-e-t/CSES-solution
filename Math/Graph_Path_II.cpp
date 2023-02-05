/*Consider a directed weighted graph having n nodes and m edges. Your task is to calculate the minimum path length from node 1 to node n with exactly k edges.

Input

The first input line contains three integers n, m and k: the number of nodes and edges, and the length of the path. The nodes are numbered 1,2,…,n.

Then, there are m lines describing the edges. Each line contains three integers a, b and c: there is an edge from node a to node b with weight c.

Output

Print the minimum path length. If there are no such paths, print −1.

Constraints

    1≤n≤100


1≤m≤n(n−1)

1≤k≤109

1≤a,b≤n

1≤c≤109


Example

Input:
3 4 8
1 2 5
2 3 4
3 1 1
3 2 2

Output:
27

*/

/*It’s a really nice problem. The procedure is almost the same as above question. We will create an Adjacency matrix where each entry stores the minimum weight edge, or   if no edge.
Next let the matrix  M subscript k   denote the answer matrix for k .
Then   M[sub(k+1)[i][j] = min( Msubk[i][l] + ADJMat[l][i]) for l =(1,,,n)    .
Here we can make an analogy with the multiplication operation. Instead we take the minimum rather than sum.
This can be tackled by matrix exponentiation, just have to modify the   function.
See my code for further clarification.
*/

// For more info refer- https://cp-algorithms.com/graph/fixed_length_paths.html#toc-tgt-1


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int MOD=1000000007;

long long int inverse(long long int i){
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

ll INF=4e18;
ll n;

vector<vll> mul(vector<vll> x, vector<vll> y) {
    vector<vll> r(n, vll(n,INF));
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < n; k++) 
        {
            for (int l = 0; l < n; l++)
            {
                r[j][k] = min(r[j][k],x[j][l]+y[l][k]);
            }
        }
    }
    return r;
}

vector<vll> modpow(vector<vll> x, ll pw) 
{
    if (pw == 1)
    {
        return x;
    }
    vector<vll> u = modpow(x, pw/2);
    u = mul(u, u);
    if (pw%2==1) u = mul(u, x);
    return u;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll m,k,a,b,c;
    cin>>n>>m>>k;
    vector<vll> v(n,vll(n,INF));
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        a--; b--;
        v[a][b]=min(v[a][b],c);
    }
    ll ans=modpow(v,k)[0][n-1];
    if(ans==INF) cout<<"-1";
    else cout<<ans;
}