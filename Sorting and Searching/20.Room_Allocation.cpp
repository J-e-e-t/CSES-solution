/*
There is a large hotel, and n customers will arrive soon. Each customer wants to have a single room.

You know each customer's arrival and departure day. Two customers can stay in the same room if the departure day of the first customer is earlier than the arrival day of the second customer.

What is the minimum number of rooms that are needed to accommodate all customers? And how can the rooms be allocated?

Input

The first input line contains an integer n: the number of customers.

Then there are n lines, each of which describes one customer. Each line has two integers a and b: the arrival and departure day.

Output

Print first an integer k: the minimum number of rooms required.

After that, print a line that contains the room number of each customer in the same order as in the input. The rooms are numbered 1,2,…,k. You can print any valid solution.

Constraints

    1≤n≤2⋅105


1≤a≤b≤109


Example

Input:
3
1 2
2 4
4 4

Output:
2
1 2 1
*/
/*
Explanation

In this problem, we're asked the minimum number of rooms needed to accommodate
$n$ customers, who arrive and leave on set days. Let's sort each customer by
their start time so that we do not have a customer arriving at say, time 3,
occupying a room before a customer that arrives at time 2.

Now, we can iterate through the customers while maintaining a minimum priority
queue that stores the departure times of customers we've already processed. For
each customer, we check to see if the minimum element in the priority queue is
less than the arrival time of the new customer.

If this is true, that means a room previously occupied has opened up, so we
remove the minimum element from the priority queue and replace it with the new
customer's departure time. The new customer will be allocated to the same room
as the customer who departed.
Otherwise, all the rooms are full, so we need to allocate another room for the
customer and add it to the priority queue.


We can determine $k$ by finding the maximum size the priority queue reaches as
we iterate through the customers.
*/

// Implementation

// Time Complexity: $\mathcal{O}(n\log n)$

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX_N = 2e5;

int N;
int ans[MAX_N];
vector<pair<pair<int, int>, int>> v(MAX_N);

int main() {
	cin >> N;
	v.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i].first.first >> v[i].first.second;
		v[i].second = i; // store the original index
	}
	sort(v.begin(), v.end());

	int rooms = 0, last_room = 0;
	priority_queue<pair<int, int>> pq; // min heap to store departure times.
	for (int i = 0; i < N; i++) {
		if (pq.empty()) {
			last_room++;
			// make the departure time negative so that we create a min heap
			// (cleanest way to do a min heap... default is max in c++)
			pq.push(make_pair(-v[i].first.second, last_room));
			ans[v[i].second] = last_room;
		}
		else {
			// accessing the minimum departure time
			pair<int, int> minimum = pq.top();
			if (-minimum.first < v[i].first.first) {
				pq.pop();
				pq.push(make_pair(-v[i].first.second, minimum.second));
				ans[v[i].second] = minimum.second;
			}

			else {
				last_room++;
				pq.push(make_pair(-v[i].first.second, last_room));
				ans[v[i].second] = last_room;
			}
		}

		rooms = max(rooms, int(pq.size()));
	}


	cout << rooms << "\n";
	for (int i = 0; i < N; i++) {
		cout << ans[i] << " ";
	}
}