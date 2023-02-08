/*
You are given an array of n integers, and your task is to find two values (at distinct positions) whose sum is x.

Input

The first input line has two integers n and x: the array size and the target sum.

The second line has n integers a1,a2,…,an: the array values.

Output

Print two integers: the positions of the values. If there are several solutions, you may print any of them. If there are no solutions, print IMPOSSIBLE.

Constraints

    1≤n≤2⋅105


1≤x,ai≤109


Example

Input:
4 8
2 7 5 1

Output:
2 
*/

#include <bits/stdc++.h>
using namespace std;
 
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
 
 
int main()
{
 
    int n, x, a;
    cin >> n >> x;
 
    vector<pair<int, int>> vec;
 
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        vec.push_back({a, i + 1});
    }
    sort(vec.begin(), vec.end());
 
    int l = 0;
    int r = vec.size() - 1;
 
    while(l<r)
    {
        if(vec[l].first+vec[r].first==x)
        {
            int a=min(vec[l].second,vec[r].second);
            int b=max(vec[l].second,vec[r].second);
            cout<<a<<" "<<b<<" \n";
            return 0;
        }
        else if(vec[l].first+vec[r].first>x)
        {
            r--;
        }
        else{
            l++;
        }
    }
    cout<<"IMPOSSIBLE";
    return 0;
}