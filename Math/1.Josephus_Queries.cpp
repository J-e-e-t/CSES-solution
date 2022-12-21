/*
Consider a game where there are n children (numbered 1,2,…,n) in a circle. During the game, every second child is removed from the circle, until there are no children left.

Your task is to process q queries of the form: "when there are n children, who is the kth child that will be removed?"

Input

The first input line has an integer q: the number of queries.

After this, there are q lines that describe the queries. Each line has two integers n and k: the number of children and the position of the child.

Output

Print q integers: the answer for each query.

Constraints

    1≤q≤105


1≤k≤n≤109


Example

Input:
4
7 1
7 3
2 2
1337 1313

Output:
2
6
1
1107
*/

// Method - We will solve the problem recursively, reducing the problem by at least half at each step. If k<n/2, we can see that the answer would be 2k. Otherwise, we have removed all the even positions. The odd positions can be renamed from 1,2,…,n2 and we can recursively find the solution for it. And then we can re-map back to our original n by multiplying by 2 and subtracting 1.
// Time complexity is O(logn).
