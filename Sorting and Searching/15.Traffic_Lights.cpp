/*
There is a street of length x whose positions are numbered 0,1,…,x. Initially there are no traffic lights, but n sets of traffic lights are added to the street one after another.

Your task is to calculate the length of the longest passage without traffic lights after each addition.

Input

The first input line contains two integers x and n: the length of the street and the number of sets of traffic lights.

Then, the next line contains n integers p1,p2,…,pn: the position of each set of traffic lights. Each position is distinct.

Output

Print the length of the longest passage without traffic lights after each addition.

Constraints

    1≤x≤109


1≤n≤2⋅105

0<pi<x


Example

Input:
8 3
3 6 2

Output:
5 3 3
*/

/*
Solution 1

Let's create a set and a multiset. The set will store the positions of the traffic lights, while the multiset will keep track of the "gaps" between the lights. The multiset keeps expanding because more lights are added, and you just need to print the length of the longest passage without traffic lights after each addition (i.e. the max element of that multiset). This element is the last element by default.

Note that when placing a new traffic light on the road, that light will split the gap between two adjacent lights into two smaller pieces, so you also have to remove the length of that gap in the multiset and add two new lengths to the multiset.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int street_len;
	int light_num;
	cin >> street_len >> light_num;

	set<int> lights{0, street_len};
	multiset<int> dist{street_len};
	for (int l = 0; l < light_num; l++) {
		int pos;
		cin >> pos;

		auto it1 = lights.upper_bound(pos);
		auto it2 = it1;
		--it2;
		
		dist.erase(dist.find(*it1 - *it2));
		dist.insert(pos - *it2);
		dist.insert(*it1 - pos);
		lights.insert(pos);
		
		auto ans = dist.end();
		--ans;
		cout << *ans << " ";
	}
}

/*
Solution 2 - Going Backwards

We'll start by trying to find the maximum gap once all the traffic lights are added. This is the last number we'll output, so we'll add it to the end of our output array. Then, we'll remove traffic lights in the reverse order to how they were added, and find the gap each removal creates.

This gap is just the distance between the two street coordinates (either a traffic light or the beginning or ending of the street) next to a given traffic light stored in our set, so we can use our set to find these values and subtract them to get our gap.

But this gap may not be the maximum gap. We'll compare this to the gap we found once all the traffic lights are added, and set the max gap to the greater value. We'll then set the next lowest element in the output array to this value, which will represent the greatest gap prior to adding the traffic light we just removed.



Implementation 1

Time Complexity: $\mathcal{O}(n \log n)$

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

int main() {
	int street_len;
	int light_num;
	std::cin >> street_len >> light_num;
	vector<int> lights(light_num);
	for (int& l : lights) {
		std::cin >> l;
	}
	// Initialize the set with beginning and ending values
	std::set<int> street_pos{0, street_len};
	for (int l : lights) {
		street_pos.insert(l);
	}

	vector<int> gaps(light_num);
	int prev = 0;
	int max_gap = 0;
	// Find the longest passage once all the streetlights are added
	for (int p : street_pos) {
		max_gap = std::max(max_gap, p - prev);
		prev = p;
	}
	gaps.back() = max_gap;

	
	//  * Remove the streetlights in reverse order to how they were added, then find
	//  * the gap created by removing each. Find the biggest current gap, and 
	//  * add it to the next lowest index in answer.
	 
	for(int i = light_num - 1; i > 0; i--) {
		street_pos.erase(lights[i]);
		auto high_it = street_pos.upper_bound(lights[i]);
		int high = *high_it;
		int low = *(--high_it);
		max_gap = std::max(max_gap, high - low);
		gaps[i - 1] = max_gap;
	}
	
	for (int i = 0; i < gaps.size() - 1; i++) {
		cout << gaps[i] << ' ';
	}
	cout << gaps.back() << endl;
}


Implementation 2

The above solution uses a sorted set. While this does make it easier to implement, it also
adds an extra $\log n$ factor to the time complexity. To remove this, we can use a
doubly linked list instead.

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

int main() {
	int street_len;
	int light_num;
	std::cin >> street_len >> light_num;
	vector<int> lights(light_num);
	for (int& l : lights) {
		std::cin >> l;
	}
	
	vector<std::pair<int, int>> sorted_lights(light_num);
	for (int l = 0; l < light_num; l++) {
		sorted_lights[l] = {lights[l], l};
	}
	std::sort(sorted_lights.begin(), sorted_lights.end());

	// Given the light position, this array stores its position in sorted_lights.
	vector<int> new_pos(light_num);
	for (int l = 0; l < light_num; l++) {
		new_pos[sorted_lights[l].second] = l;
	}

	struct Light {
		int prev, next;
		int pos;
	};
	vector<Light> light_ll(light_num + 2);
	// First, we set our "lights" on the edges of the street.
	light_ll[0] = {-1, 1, 0};
	light_ll[light_num + 1] = {light_num, -1, street_len};
	for (int l = 0; l < light_num; l++) {
		light_ll[l + 1] = {l, l + 2, sorted_lights[l].first};
	}
	
	// Find the longest passage once all the streetlights are added
	vector<int> gaps(light_num);
	int max_gap = 0;
	for (int l = 0; l <= light_num; l++) {
		max_gap = std::max(max_gap, light_ll[l + 1].pos - light_ll[l].pos);
	}
	gaps.back() = max_gap;

	// Remove the streetlights in reverse order like as we did in the above solution.
	for (int l = light_num - 1; l > 0; l--) {
		Light to_del = light_ll[new_pos[l] + 1];
		Light& left = light_ll[to_del.prev];
		Light& right = light_ll[to_del.next];
		// Re-assign the references to the next & previous node
		left.next = to_del.next;
		right.prev = to_del.prev;

		max_gap = std::max(max_gap, right.pos - left.pos);
		gaps[l - 1] = max_gap;
	}

	for (int i = 0; i < gaps.size() - 1; i++) {
		cout << gaps[i] << ' ';
	}
	cout << gaps.back() << endl;
}
*/