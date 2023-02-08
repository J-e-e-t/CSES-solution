/*
You are given a playlist of a radio station since its establishment. The playlist has a total of n songs.

What is the longest sequence of successive songs where each song is unique?

Input

The first input line contains an integer n: the number of songs.

The next line has n integers k1,k2,…,kn: the id number of each song.

Output

Print the length of the longest sequence of unique songs.

Constraints

    1≤n≤2⋅105


1≤ki≤109


Example

Input:
8
1 2 1 3 2 7 4 2

Output:
5
*/

// Step -1 store value in hashmap so that we can check that song played before or not.
// step -2 make two-pointer i and j if v[i] has occurred earlier remove all element till v[i] and update ans.new length will be (i-j).
// Step 3- if v[i]  not occurred simply update ans by one.

#include<bits/stdc++.h>
using namespace std;
#define int long long int
int32_t main(){
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<int > v;
	map<int ,bool > mymap;
	int maxx=0;
	int currans=0;
	int j=0;
	for(int i=0;i<n;i++){
	    int k;
        cin>>k;
        v.push_back(k);
        if(mymap.find(k)==mymap.end()||mymap[k]==false){
                mymap[k]=true;
                currans++;
                maxx=max(currans,maxx);

        }
        else{
             while(v[j]!=k){
                    mymap[v[j]]=false;
                    j++;
             }
             //j++;
            // mymap[v[j]]=true;
             currans=(i-j);
             j++;


        }
	}
	cout<<maxx<<endl;

}

/*
 ll n;cin>>n;
 ll a[mx];
 for(ll i=0;i<n;++i)
 {
   cin>>a[i];
 }
 map<ll,ll>mp;
 ll ans=0;
 for(ll i=0,j=0;i<n;++i)
 {
    j=max(mp[a[i]],j);
    ans=max(ans,i-j+1);
    mp[a[i]]=i+1;
 }
 cout<<ans<<"\n";  
 */


/*


int n;

set<int> s;

int a[200000], ans;


int main() {

	int r = -1;

	cin >> n; F0R(i,n) cin >> a[i];

	F0R(i,n) {

		while (r < n-1 && !s.count(a[r+1])) s.insert(a[++r]);

		ans = max(ans,r-i+1);

		s.erase(a[i]);

	}

	cout << ans;

}*/