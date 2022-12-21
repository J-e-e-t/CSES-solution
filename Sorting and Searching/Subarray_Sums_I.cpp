/*
     Time limit: 1.00 s Memory limit: 512 MB 

Given an array of n positive integers, your task is to count the number of subarrays having sum x.

Input

The first input line has two integers n and x: the size of the array and the target sum x.

The next line has n integers a1,a2,…,an: the contents of the array.

Output

Print one integer: the required number of subarrays.

Constraints

    1≤n≤2⋅105


1≤x,ai≤109


Example

Input:
5 7
2 4 1 2 7

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long

void solve(){
    ll n,x;
    cin>>n>>x;

    vector<ll> a(n+1),pre(n+1);

    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    pre[0]=0;
    pre[1]=a[1];
    for(int i=2;i<=n;i++){
        pre[i]=pre[i-1]+a[i];
    }

    int left = 1;
    int right = 1;
    int count=0;
    ll sum = 0;

    while(left<n && right<n){

        while(right<n){
            sum = pre[right]-pre[left-1];
            
            if(sum==x){
                count++;
            }
            right++;
            if(right==n || (pre[right]-pre[left-1]>x)){
                right--;
                break;
            }
            
        }
        left++;
    } 
    cout<<count<<endl;

}

int main(){
    solve();
}