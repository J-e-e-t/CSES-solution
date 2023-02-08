/*
Given an array of n integers, your task is to find the maximum sum of values in a contiguous, nonempty subarray.

Input

The first input line has an integer n: the size of the array.

The second line has n integers x1,x2,…,xn: the array values.

Output

Print one integer: the maximum subarray sum.

Constraints

    1≤n≤2⋅105


−109≤xi≤109


Example

Input:
8
-1 3 -2 5 3 -5 2 2

Output:
9
*/

#include <bits/stdc++.h>
using namespace std;
 
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
int main()
{
 
    int n;
    cin >> n;
    long long arr[n];
 
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
 
    long long mx = -1e9;
 
    long long sum = max(0, arr[0]);
 
    for (int i = 1; i < n; i++)
    {
        if (arr[i] + sum > 0)
        {
            sum += arr[i];
            mx = max(mx, sum);
        }
        else
        {
            sum = max(0, arr[i]);
        }
    }
    for(int i=0;i<n;i++)
    {
        mx=max(arr[i],mx);
    }
    cout << mx;
}