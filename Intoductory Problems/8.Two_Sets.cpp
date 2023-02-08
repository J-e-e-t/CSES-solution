/*
Your task is to divide the numbers 1,2,…,n into two sets of equal sum.

Input

The only input line contains an integer n.

Output

Print "YES", if the division is possible, and "NO" otherwise.

After this, if the division is possible, print an example of how to create the sets. First, print the number of elements in the first set followed by the elements themselves in a separate line, and then, print the second set in a similar way.

Constraints

    1≤n≤106


Example 1

Input:
7

Output:
YES
4
1 2 4 7
3
3 5 6

Example 2

Input:
6

Output:
NO
*/

#include <bits/stdc++.h>
using namespace std;
 
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
 
int main()
{
    long long n;
    cin>>n;
  
    long long sum= n*(n+1)/2;
 
    if(sum&1){
        cout<<"NO";
        return 0;
    }else{
        sum/=2;
        vector<long long> vec1,vec2;
        while(n){
            if(sum-n>=0)
            {
                vec1.push_back(n);
                sum-=n;
                
            }else{
                vec2.push_back(n);
                
            }
            n--;
        }
 
        cout<<"YES \n";
        cout<<vec1.size()<<"\n";
        for(auto it:vec1)
        {
            cout<<it<<" ";
        }
        cout<<"\n"<<vec2.size()<<"\n";
        for(auto it:vec2)
        {
            cout<<it<<" ";
        }
    }
}