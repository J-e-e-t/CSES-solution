/*
There are n sticks with some lengths. Your task is to modify the sticks so that each stick has the same length.

You can either lengthen and shorten each stick. Both operations cost x where x is the difference between the new and original length.

What is the minimum total cost?

Input

The first input line contains an integer n: the number of sticks.

Then there are n integers: p1,p2,…,pn: the lengths of the sticks.

Output

Print one integer: the minimum total cost.

Constraints

    1≤n≤2⋅105


1≤pi≤109


Example

Input:
5
2 3 1 5 2

Output:
5
*/

#include <bits/stdc++.h>
using namespace std;
 
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr + n);
 
    long long m;
    if (n & 1)
    {
        m = arr[n / 2];
    }
    else
    {
        m = (arr[(n / 2)] + arr[(n / 2) - 1]) / 2;
    }
 
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        if(arr[i] - m>=0){
            ans+=(arr[i]-m);
        }
        else{
            ans+=(m-arr[i]);
        }
    }
    cout<<ans;
}
