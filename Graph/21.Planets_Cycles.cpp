/*
You are playing a game consisting of n planets. Each planet has a teleporter to another planet (or the planet itself).

You start on a planet and then travel through teleporters until you reach a planet that you have already visited before.

Your task is to calculate for each planet the number of teleportations there would be if you started on that planet.

Input

The first input line has an integer n: the number of planets. The planets are numbered 1,2,…,n.

The second line has n integers t1,t2,…,tn: for each planet, the destination of the teleporter. It is possible that ti=i.

Output

Print n integers according to the problem statement.

Constraints

    1≤n≤2⋅105


1≤ti≤n


Example

Input:
5
2 4 3 1 4

Output:
3 3 1 3 4*/

/*
Define the number of teleportations starting from a planet as the
$\texttt{pathlength}$ of that planet. For each planet that hasn't been visited,
we want to find its $\texttt{pathlength}$. Call the planet we are performing
$\texttt{dfs}$ from the $\textit{start}$. As we perform $\texttt{dfs}$ from the
$\textit{start}$, keep track of the planets seen, in order, in the
$\texttt{path}$ queue and keep track of $\texttt{steps}$, the length of the path
(which is also the $\texttt{pathlength}$ of the $\textit{start}$). When we reach
a planet that has already been visited (call this planet the $\textit{repeat}$),
add the $\texttt{pathlength}$ of the $\textit{repeat}$ to the current
$\texttt{step}$ count because we would continue to visit all of the planets that
$\textit{repeat}$ would go on to visit.

Once we have $\texttt{path}$ and $\texttt{steps}$ we can calculate the
$\texttt{pathlength}$ of all the planets in this $\texttt{path}$. We know the
$\textit{repeat}$ will always be the planet at the end of the $\texttt{path}$,
but it may appear elsewhere as well. We can break this down into two cases:

The $\textit{repeat}$ was visited twice in the current $\texttt{path}$. The
planets in the $\texttt{path}$ between the two occurrences of the
$\textit{repeat}$ form a $\textit{cycle}$.
The $\textit{repeat}$ only appears at the end of the current $\texttt{path}$.
All of the planets in the $\texttt{path}$ are not part of a $\textit{cycle}$.


For planets inside a $\textit{cycle}$, the repeating planet when starting from
that planet is itself. For all the planets in the $\texttt{path}$ but outside
the $\textit{cycle}$, the planet that repeats when starting from each planet
will still be the $\textit{repeat}$.

Since the planets outside the $\textit{cycle}$ all have paths ending at the
$\textit{repeat}$, each one's $\texttt{pathlength}$ is $1$ less than the
previous'. So, as we iterate through the planets along the $\texttt{path}$ that
are outside the $\textit{cycle}$, the $\texttt{pathlength}$ will decrease by $1$
each time, starting from the $\textit{start}$ with a $\texttt{pathlength}$ of
$\texttt{steps}$. Once we get to the $\textit{cycle}$, the $\texttt{pathlength}$
of the planets will all be equal to the $\texttt{pathlength}$ of the
$\textit{repeat}$, which is the length of the $\textit{cycle}$.*/

#include <iostream>
#include <queue>
using namespace std;
void dfs(int planet);

bool visited[200000]{};
int destinations[200000];
int pathlength[200000]{};
queue<int> path;
int steps = 0;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> destinations[i];
		destinations[i]--;
	}
	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			steps = 0;
			dfs(i);
			int decrement = 1;
			//for each planet in current path, calculate pathlength
			while (!path.empty())
			{
				//we are in the cycle; all nodes have same pathlength
				if (path.front() == path.back())
				{
					decrement = 0;
				}
				pathlength[path.front()] = steps;
				steps -= decrement;
				path.pop();
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << pathlength[i] << " ";
	}
	cout << endl;
	return 0;
}

void dfs(int planet)
{
	//add planet to path
	path.push(planet);
	if (visited[planet])
	{
		//add pathlength of the repeat planet to current step count
		steps += pathlength[planet];
		return;
	}
	visited[planet] = true;
	steps++;
	dfs(destinations[planet]);
}