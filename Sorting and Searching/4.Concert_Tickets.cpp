/*
There are n concert tickets available, each with a certain price. Then, m customers arrive, one after another.

Each customer announces the maximum price they are willing to pay for a ticket, and after this, they will get a ticket with the nearest possible price such that it does not exceed the maximum price.

Input

The first input line contains integers n and m: the number of tickets and the number of customers.

The next line contains n integers h1,h2,…,hn: the price of each ticket.

The last line contains m integers t1,t2,…,tm: the maximum price for each customer in the order they arrive.

Output

Print, for each customer, the price that they will pay for their ticket. After this, the ticket cannot be purchased again.

If a customer cannot get any ticket, print −1.

Constraints

    1≤n,m≤2⋅105


1≤hi,ti≤109


Example

Input:
5 3
5 3 7 8 5
4 8 3

Output:
3
8
-1*/


#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define REP(i, a, n) for (int i = a; i < n; i++)
#define REP1(i, a, n) for (int i = a; i <= n; i++)
#define all(x) (x).begin(), (x).end()
 
int main()
{
	int n, m;
	cin >> n >> m;
 
	vector<long long> tick(n);
	vector<long long> cust(m);
 
	multiset<long long> myset;
 
	REP(i, 0, n)
	{
		cin >> tick[i];
		myset.insert(tick[i]);
	}
	REP(i, 0, m)
	{
		cin >> cust[i];
	}
 
	REP(i, 0, m)
	{
		ll a = cust[i];
 
		auto pos = myset.upper_bound(a);
		if (pos == myset.begin())
		{
			cout << -1 << "\n";
			continue;
		}
		pos--;
 
		cout << *pos << "\n";
		myset.erase(pos);
	}
}
