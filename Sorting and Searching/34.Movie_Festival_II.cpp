/*
In a movie festival, n movies will be shown. Syrjälä's movie club consists of k members, who will be all attending the festival.

You know the starting and ending time of each movie. What is the maximum total number of movies the club members can watch entirely if they act optimally?

Input

The first input line has two integers n and k: the number of movies and club members.

After this, there are n lines that describe the movies. Each line has two integers a and b: the starting and ending time of a movie.

Output

Print one integer: the maximum total number of movies.

Constraints

    1≤k≤n≤2⋅105


1≤a<b≤109


Example

Input:
5 2
1 5
8 10
3 6
2 5
6 9

Output:
4*/


/*
Explanation

The first step is the same as that of
Movie Festival; sort
the movies in increasing order of end time. For each movie in order, we will
assign it to one of the $k$ members to watch (or none of them).

Keep track of the time each member finishes watching all of his currently
assigned movies in an ordered multiset
(represented by
a TreeMap in Java or a multiset in C++). Initially, the collection consists of $k$ zeroes.

For each movie in order, we can assign a member to watch it if there exists an
element in the sorted collection less than or equal to the start time of the
movie. If there are multiple such elements, choose the greatest one (the member
who finished watching his assigned movies the latest). Assign the member to
watch this movie by incrementing the answer and updating the collection
accordingly.*/

//Time Complexity:
 
// $\mathcal{O}(n\log k)$

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<pair<int, int>> v(n);
	for (int i = 0; i < n; i++) // read start time, end time
		cin >> v[i].second >> v[i].first;
	sort(begin(v), end(v)); // sort by end time

	int maxMovies = 0;
	multiset<int> end_times; // times when members will finish watching movies
	for (int i = 0; i < k; ++i)
		end_times.insert(0);

	for (int i = 0; i < n; i++) {
		auto it = end_times.upper_bound(v[i].second);
		if (it == begin(end_times)) continue;
		// assign movie to be watched by member in multiset who finishes at time *prev(it)
		end_times.erase(--it);
		// member now finishes watching at time v[i].first
		end_times.insert(v[i].first);
		++maxMovies;
	}

	cout << maxMovies;
}