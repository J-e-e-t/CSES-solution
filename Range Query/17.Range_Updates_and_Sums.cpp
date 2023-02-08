/*Range Updates and Sums

Your task is to maintain an array of n values and efficiently process the following types of queries:

    Increase each value in range [a,b]

by x
.
Set each value in range [a,b]
to x
.
Calculate the sum of values in range [a,b]

    .

Input

The first input line has two integers n and q: the array size and the number of queries.

The next line has n values t1,t2,…,tn: the initial contents of the array.

Finally, there are q lines describing the queries. The format of each line is one of the following: "1 a b x", "2 a b x", or "3 a b".

Output

Print the answer to each sum query.

Constraints

    1≤n,q≤2⋅105


1≤ti,x≤106

1≤a≤b≤n


Example

Input:
6 5
2 3 1 1 5 3
3 3 5
1 2 4 2
3 3 5
2 2 4 5
3 3 5

Output:
7
11
15

*/

/*
No surprises here. My solution will use the data structure and the technique related to that data structure which most would have already guessed after reading the problem statement. The important thing would be a thorough understanding of the concept and a neat implementation(I have tried to make it readable).
what data structure, what technique?

We will use a segment tree with lazy propagation. If you have an alternate approach, please share.

Alright so our segment tree needs to support the following operations :
1. increase values in range [l,r] by x.
2. set values in range [l,r] = x.
3. return sum of values in range [l,r].

Think about what information should we store per node of the tree, so that we are able to lazily update our nodes when a new update comes in and we are able to propagate the updates downward when needed.

To better understand lazy propagation, I recommend reading this : Super amazing theory in 1 comment (My implementation uses applyAggr and compose functions mentioned here).
What info to store per node?

Ofcourse both the updates are needed to be stored along with the sum, what do they represent?

Let's keep the following variables per node:
1. setAll
2. increment
3. Sum : The sum of the values in range [l,r](the range represented by the node)

Representation : All the values in range [l,r] should be set to the value "setAll" and then their values should be increased by "increment". Initially, we may set increment to 0 but then what about setAll? if we set setAll to 0 it would mean all values are 0. So we need an indicator that tells if the value given by setAll is valid or invalid.

So let us also keep another variable setAllValid per node which is 1 if the value given by setAll is valid otherwise 0.
How do I find the actual Sum using these variables?

if setAll is valid, finding sum is quite easy. If L is the number of elements in the subarray which this node represents then our sum will simply be L * (setAll + increment).
if setAll is invalid, then whatever is the value of the sum variable we should add (L * increment) to it.
How do i propagate these updates downward?

First apply them to the node and calculate the sum for this node.
Next push the updates down to the children.
Now the child nodes may have updates of their own as well, how to combine these updates?
Updates propagated down are always more recent.
So if parent node had setAllValid = 1, then all updates in child node are overwritten by the parent update values otherwise the increment of parent and increment of child node summed up make the new increment of the child node and rest everything stays same.

Also after you have pushed the updates down, you may reset the updates of the parent back to default values(increment = 0, setAllValid = 0)

Time Complexity is logN per query.
If something is not explained or if something isn't clear feel free to ask but I recommend understanding lazy prop well before attempting the problem or reading the editorial.
AC code : https://ideone.com/8HQxMk
*/

/*
    author: kartik8800
*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(ll i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;

struct node
{
    ll sum;
    ll setAll;
    ll increment;
    bool setAllValid;
    node()
    {
       sum = 0;
       setAllValid = 0;
       increment = 0;
    }
    void Reset()
    {
       setAllValid = increment = 0;
    }
};

class segtree
{
    int range;
    vector<node> tree;
public:
    void build(vector<int>& v)
    {
        range = v.size();
        tree.assign(4*range, node());
        build_recur(v, 0, range-1, 0);
    }
    void build_recur(vector<int>& v, int l, int r, int node_no)
    {
        if(l == r){
            if(l < v.size())
                tree[node_no].sum = v[l];
            else tree[node_no].sum = 0;
            return;
        }
        int mid = (l+r)/2;
        build_recur(v, l, mid, 2*node_no + 1);
        build_recur(v, mid + 1, r, 2*node_no + 2);
        tree[node_no].sum = tree[2*node_no + 1].sum + tree[2*node_no + 2].sum;
    }
    ll range_query(int L, int R)
    {
        return range_query_recur(0, 0, range - 1, L, R);
    }

    void incUpdate_recur(int node, int l, int r, int& L, int& R, int& X)
    {
        if(r < L || R < l || l >= range)
            return;
        if(L <= l && R >= r)
        {
            tree[node].increment += X;
            return;
        }
        applyAggr(node,l,r);
        int mid = (l+r)/2;
        incUpdate_recur(2*node+1,l,mid,L,R,X);
        incUpdate_recur(2*node+2,mid+1,r,L,R,X);
        applyAggr(2*node+1, l, mid);
        applyAggr(2*node+2, mid+1, r);
        tree[node].sum = tree[2*node+1].sum + tree[2*node+2].sum;
    }

    void incUpdate(int L, int R, int X)
    {
        incUpdate_recur(0,0,range-1,L,R,X);
    }

    void setUpdate_recur(int node, int l, int r, int& L, int& R, int& X)
    {
        if(r < L || R < l || l >= range)
            return;
        if(L <= l && R >= r)
        {
            tree[node].setAllValid = 1;
            tree[node].setAll = X;
            tree[node].increment = 0;
            return;
        }
        applyAggr(node,l,r);
        int mid = (l+r)/2;
        setUpdate_recur(2*node+1,l,mid,L,R,X);
        setUpdate_recur(2*node+2,mid+1,r,L,R,X);
        applyAggr(2*node+1, l, mid);
        applyAggr(2*node+2, mid+1, r);
        tree[node].sum = tree[2*node+1].sum + tree[2*node+2].sum;
    }

    void setUpdate(int L, int R, int X)
    {
        setUpdate_recur(0,0,range-1,L,R,X);
    }

    void compose(int par, int child)
    {
        if(tree[par].setAllValid){
            tree[child].setAllValid = 1;
            tree[child].setAll = tree[par].setAll;
            tree[child].increment = tree[par].increment;
        }
        else tree[child].increment += tree[par].increment;
    }

    void applyAggr(int node, int l, int r)
    {
        if(tree[node].setAllValid)
            tree[node].sum = (r-l+1)*tree[node].setAll;

        tree[node].sum += (r-l+1)*tree[node].increment;

        if(l != r){
            compose(node, 2*node + 1);
            compose(node, 2*node + 2);
        }

        tree[node].Reset();
    }

    ll range_query_recur(int node, int l, int r, int& L, int& R)
    {
        if(r < L || R < l || l >= range)
            return 0;
        applyAggr(node, l, r);
        if(L <= l && R >= r)
            return tree[node].sum;
        int mid = (l+r)/2;
        return range_query_recur(2*node + 1, l, mid, L, R) + range_query_recur(2*node + 2, mid+1, r, L, R);
    }
};

int main() {
   fast_io;
   int n,q;
   cin >> n >> q;

   vector<int> v(n);
   for(int i = 0; i < n; i++)
        cin >> v[i];

   segtree sg;
   sg.build(v);

   while(q--)
   {
        int t;
        cin >> t;
        if(t == 1){
            int a,b,x;
            cin >> a >> b >> x;
            sg.incUpdate(a-1,b-1,x);
        }
        else if(t == 2){
            int a,b,x;
            cin >> a >> b >> x;
            sg.setUpdate(a-1,b-1,x);
        }
        else {
            int a,b;
            cin >> a >> b;
            cout << sg.range_query(a-1,b-1) <<'\n';
        }
   }
   return 0;
}
