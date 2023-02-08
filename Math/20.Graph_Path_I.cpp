/*
 Consider a directed graph that has n nodes and m edges. Your task is to count the number of paths from node 1 to node n with exactly k edges.

Input

The first input line contains three integers n, m and k: the number of nodes and edges, and the length of the path. The nodes are numbered 1,2,…,n.

Then, there are m lines describing the edges. Each line contains two integers a and b: there is an edge from node a to node b.

Output

Print the number of paths modulo 109+7.

Constraints

    1≤n≤100


1≤m≤n(n−1)

1≤k≤109

1≤a,b≤n


Example

Input:
3 4 8
1 2
2 3
3 1
3 2

Output:
2

Explanation: The paths are 1→2→3→1→2→3→1→2→3 and 1→2→3→2→3→2→3→2→3.
*/
// https://cp-algorithms.com/graph/fixed_length_paths.html

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD=1000000007;
using vll = vector<ll>;


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

ll n;

vector<vll> mul(vector<vll> x, vector<vll> y) {
    vector<vll> r(n, vll(n));
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < n; k++) 
        {
            for (int l = 0; l < n; l++)
            {
                r[j][k] = (r[j][k]+(x[j][l]*y[l][k])%MOD)%MOD;
            }
        }
    }
    return r;
}

vector<vll> modpow(vector<vll> x, ll pw) 
{
    if (pw == 0)
    {
        vector<vll> r(n, vll(n));
        for (int i = 0; i < n; i++) r[i][i] = 1;
        return r;
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
    ll m,k,a,b;
    cin>>n>>m>>k;
    vector<vll> v(n,vll (n,0));
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        a--; b--;
        v[a][b]++;
    }
    cout<<modpow(v,k)[0][n-1];
}