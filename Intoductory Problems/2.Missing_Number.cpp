/*
You are given all numbers between 1,2,…,n except one. Your task is to find the missing number.

Input

The first input line contains an integer n.

The second line contains n−1 numbers. Each number is distinct and between 1 and n (inclusive).

Output

Print the missing number.

Constraints

    2≤n≤2⋅105


Example

Input:
5
2 3 1 5

Output:
4
*/
/*
 There are several solutions to this problem including sorting and searching to find the missing number. Even though those solutions are valid I will use a neat number theory trick to solve this one. It's a known fact amongst mathematicians that the sum of all the natural numbers up to a certain N (where N is finite) can be calculated by the following expression:

 n(n+1)/2  
 
 By knowing this property of the natural numbers a simple solution emerges. Since we know there is only one number missing in the permutation [1, N] then we can subtract the sum of the input from the sum of all the natural numbers up to N, by doing this every number will cancel out except one, the missing number. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long int n, input, sum = 0;
    cin >> n;

    for (int i = 0 ; i < n - 1 ; i++) {
        cin >> input;
        sum += input;
    }

    cout << ( n * (n + 1) ) / 2 - sum << endl;

    return 0;
}


//This algorithm runs in time complexity of O(N) and space complexity of O(1) and it seems to me that it is indeed the most efficient approach to the problem.
