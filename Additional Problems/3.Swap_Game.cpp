/*
You are given a 3×3 grid containing the numbers 1,2,…,9. Your task is to perform a sequence of moves so that the grid will look like this:

1 2 3
4 5 6
7 8 9

On each move, you can swap the numbers in any two adjacent squares (horizontally or vertically). What is the minimum number of moves required?

Input

The input has three lines, and each of them has three integers.

Output

Print one integer: the minimum number of moves.

Example

Input:
2 1 3
7 5 9
8 4 6

Output:
4
*/


/*
Explanation

Since there are only $9!$ states the grid can be in, we can use BFS to find the
number of moves needed to reach the $\texttt{target}$ from the starting grid. We
represent each grid as a number in base $9$.

For each grid, we can swap two horizontally adjacent squares or two vertically
adjacent squares. If we haven't processed this new grid yet, we can push the new
grid and distance into the queue and mark it as visited in the $\texttt{vis}$
array. When we reach the sorted grid, we print the $\texttt{dist}$.


Implementation

Time Complexity: $\mathcal{O}(N^2!)$, where $N$ is the side length of the
grid

*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int powers[10];

// swap two pieces and return the new grid
int move(int grid, int i, int j)
{
	int a = grid % powers[i + 1] / powers[i];
	int b = grid % powers[j + 1] / powers[j];
	return grid - a * powers[i] - b * powers[j] + b * powers[i] + a * powers[j];
}

int main()
{
	powers[0] = 1;
	for (int i = 1; i < 10; i++)
	{
		powers[i] = 9 * powers[i - 1];
	}
	vector<bool> vis(powers[9], false);
	// the final grid we want to reach
	int target = 0;
	for (int i = 8; i >= 0; i--)
	{
		target += (8 - i) * powers[i];
	}
	int grid = 0, num;
	for (int i = 8; i >= 0; i--)
	{
		cin >> num;
		grid += (num - 1) * powers[i];
	}
	queue<pair<int, int>> q;
	q.push({grid, 0});
	while (!q.empty())
	{
		auto [g, dist] = q.front();
		q.pop();
		// if we've reached the target, we can print the number of moves
		if (g == target)
		{
			cout << dist << endl;
			return 0;
		}
		// swap two horizontally adjacent pieces
		for (int i = 0; i < 8; i++)
		{
			if (i % 3 == 2)
			{
				continue;
			}
			int swapped = move(g, 8 - i, 8 - (i + 1));
			if (!vis[swapped])
			{
				q.push({swapped, dist + 1});
				vis[swapped] = true;
			}
		}
		// swap two vertically adjacent pieces
		for (int i = 0; i < 6; i++)
		{
			int swapped = move(g, 8 - i, 8 - (i + 3));
			if (!vis[swapped])
			{
				q.push({swapped, dist + 1});
				vis[swapped] = true;
			}
		}
	}
	return 0;
}