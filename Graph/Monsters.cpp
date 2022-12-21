/*
You and some monsters are in a labyrinth. When taking a step to some direction in the labyrinth, each monster may simultaneously take one as well. Your goal is to reach one of the boundary squares without ever sharing a square with a monster.

Your task is to find out if your goal is possible, and if it is, print a path that you can follow. Your plan has to work in any situation; even if the monsters know your path beforehand.

Input

The first input line has two integers n and m: the height and width of the map.

After this there are n lines of m characters describing the map. Each character is . (floor), # (wall), A (start), or M (monster). There is exactly one A in the input.

Output

First print "YES" if your goal is possible, and "NO" otherwise.

If your goal is possible, also print an example of a valid path (the length of the path and its description using characters D, U, L, and R). You can print any path, as long as its length is at most n⋅m steps.

Constraints

    1≤n,m≤1000


Example

Input:
5 8
########
#M..A..#
#.#.M#.#
#M#..#..
#.######

Output:
YES
5
RRDDR
*/

/*Abstract

We want to find if A can reach the edge of the maze without being touched by monsters by BFS. If possible, retrace and print its path.

Solution

Because the monsters move optimally, if a monster can reach a location in the maze before A, then A may never move to that spot. Thus, for A to enter a spot, the distance from that location to A must be less than the distance from that location to the nearest monster. Knowing this, we may BFS to find all locations that are visitable by A. This will run in N2N2 time because each location will be visited a constant amount of times.

While conducting the bfs, store the previous location of every location ("from" array in code below). This way, once A reaches the edge, we can retrace A's path, following the path of previous locations and storing the direction traveled.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <algorithm>
#define pii pair<int, int>
#define mn 1005
using namespace std;

int N, M;
queue<pii> q;
int paths[mn][mn];
pii from[mn][mn];
int oo = INT_MAX;
pii A;
string ans;
bool possible = false;

void retrace(pii node){  // retrace from final node, adding direction from previous node to a string. This string will be backwards but will be reversed before output.
	pii origin = from[node.first][node.second];
	if(origin ==  pii(0,0)) return;
	if(origin.first == node.first+1) ans.push_back('U');
	if(origin.first == node.first-1) ans.push_back('D');
	if(origin.second == node.second+1) ans.push_back('L');
	if(origin.second==node.second-1) ans.push_back('R');
	retrace(origin);

}
void check(pii origin, pii dest){ // check if the considered destination may be traveled to
	int pl = paths[origin.first][origin.second];
	if(pl+1<paths[dest.first][dest.second]){
		paths[dest.first][dest.second]  = pl+1;
		q.push(dest);
		from[dest.first][dest.second] = origin;
	}
}
bool mora = false; // false if bfs for monsters, true if bfs for A
void bfs(){
	while(!q.empty()){
		pii loc = q.front(), next; q.pop();
		next = loc; next.first++; check(loc, next); // go through adjacent locations
		next = loc; next.first--; check(loc, next);
		next = loc; next.second++; check(loc, next);
		next = loc; next.second--; check(loc, next);
		if(mora && (loc.first == 1 || loc.second == 1 || loc.first == N || loc.second == M)){
			cout << "YES" << endl;
			cout << paths[loc.first][loc.second] << endl;
			retrace(loc);
			possible = true;
			return;
		}
	}
}
int main() {
	cin >> N >> M;
	for(int i = 1; i <= N; i++){
		string s;
		cin >> s;
		for(int j = 1; j <= M; j++){
			paths[i][j] = oo;
			if(s[j-1] == '#') paths[i][j] = 0;
			if(s[j-1] == 'M') {q.push(pii(i,j)); paths[i][j]  = 0;}
			if(s[j-1] == 'A') {A.first = i; A.second = j;}
		}
	}
	bfs(); // monster bfs
	mora = true; // change next bfs to A bfs
	from[A.first][A.second] = pii(0,0); // give the retrace a terminating location
	paths[A.first][A.second] = 0; q.push(A); // get ready for next bfs
	bfs(); // bfs with A
	if(possible){
		reverse(ans.begin(), ans.end());
		cout << ans << endl;
	}
	else cout << "NO" << endl;
}
