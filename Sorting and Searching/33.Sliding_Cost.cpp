/*
You are given an array of n integers. Your task is to calculate for each window of k elements, from left to right, the minimum total cost of making all elements equal.

You can increase or decrease each element with cost x where x is the difference between the new and the original value. The total cost is the sum of such costs.

Input

The first input line contains two integers n and k: the number of elements and the size of the window.

Then there are n integers x1,x2,…,xn: the contents of the array.

Output

Output n−k+1 values: the costs.

Constraints

    1≤k≤n≤2⋅105


1≤xi≤109


Example

Input:
8 3
2 4 3 5 8 1 2 1

Output:
2 2 5 7 7 1
*/

/*

Time Complexity:
 
$\mathcal{O}(N\log K)$

Abstract

Finding the difference between sums of the upper $K/2$ elements and lower $K/2$
with two multisets.


Warning!

The implementation of this solution assumes familarity with Sliding Median as their implementations are near identical.

Solution
The cost of a window

It can be shown that it is optimal to change the values of the window to the median (left as an exercise :D). Once we find the median, we must find the sum of the distances of all elements to the median. Summing the distances for each element individually is too slow. Instead, we'll split the elements in the window into two groups and calculate the cost as described below. The smallest K/2K/2 elements in the window will be in the lower group while the largest K/2K/2 elements in the window will be in the upper group.

The cost of the window can be expressed as a function of K,S1,S2K,S1​,S2​, and MM, where S1S1​ and S2S2​ denote the sum of elements in the lower and upper group respectively, and MM denotes the median of the window. The cost of the lower group will be ∑i=1K/2M−ei∑i=1K/2​M−ei​, and the cost of the upper group will be ∑i=1K/2ei−M∑i=1K/2​ei​−M, where ee represents an element in the group. These expressions can be simplified to M×K/2−S1M×K/2−S1​ and S2−M×K/2S2​−M×K/2. The total cost of the window is the sum of the costs contributed by both groups, or S2−S1S2​−S1​.

Implementation

Finding the difference between the largest $K/2$ elements in the window and the
smallest $K/2$ elements in the window is similar to finding the sliding median
(more info here). To maintain the current cost,
we keep track of the sum of each multiset as we insert and erase. Using the
double multiset method described in the Sliding Median solution, we let the
lower group include the lower $\lceil K/2 \rceil$ elements in the window. As a
result, when the window size is odd, the lower group has one more than element
than the desired amount. We can correct for this by adding the median to the
final answer if the window size is odd.
*/

#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;
const ll mn = (ll) 2e5+5;

ll N, K;
ll arr[mn];
multiset<ll> up;
multiset<ll> low;
ll sLow, sUp;

void ins(ll val){
	ll a = *low.rbegin();
	if(a < val){
		up.insert(val); sUp += val;
		if(up.size() > K/2){
			ll moving = *up.begin();
			low.insert(moving); sLow += moving;
			up.erase(up.find(moving)); sUp -= moving;
		}
	}
	else{
		low.insert(val); sLow += val;
		if(low.size() > (K + 1)/2){
			ll moving = *low.rbegin();
			up.insert(*low.rbegin()); sUp += moving;
			low.erase(low.find(*low.rbegin())); sLow -= moving;
		}
	}
}

void er(ll val){
	if(up.find(val) != up.end()) up.erase(up.find(val)), sUp -= val;
	else low.erase(low.find(val)), sLow -= val;
	if(low.empty()){
		ll moving = *up.begin();
		low.insert(*up.begin()); sLow += moving;
		up.erase(up.find(*up.begin())); sUp -= moving;
	}
}

ll med(){ return (K%2 == 0) ? 0 : (*low.rbegin()); }

int main() {
	cin >> N >> K;
	for(ll i = 0; i < N; i++) cin >> arr[i];
	low.insert(arr[0]); sLow += arr[0];
	for(ll i = 1; i < K; i++) ins(arr[i]);
	cout << sUp - sLow + med(); if(N!=1) cout << " ";
	for(ll i = K; i < N; i++){
		if(K == 1){
			ins(arr[i]);
			er(arr[i - K]);
		}
		else{
			er(arr[i - K]);
			ins(arr[i]);
		}
		cout << sUp - sLow + med(); if(i != N -1) cout << " ";
	}
	cout << endl;
}
