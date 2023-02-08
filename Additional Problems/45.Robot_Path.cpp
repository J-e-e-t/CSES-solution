/*
You are given a description of a robot's path. The robot begins at point (0,0) and performs n commands. Each command moves the robot some distance up, down, left or right.

The robot will stop when it has performed all commands, or immediately when it returns to a point that it has already visited. Your task is to calculate the total distance the robot moves.

Input

The first input line has an integer n: the number of commands.

After that, there are n lines describing the commands. Each line has a character d and an integer x: the robot moves the distance x to the direction d. Each direction is U (up), D (down), L (left), or R (right).

Output

Print the total distance the robot moves.

Constraints

    1≤n≤105


1≤x≤106


Example

Input:
5
U 2
R 3
D 1
L 5
U 2

Output:
9
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;

    int x=0;
    int y=0;

    set<string> s;
    s.insert("0$0");

    while(t--){
        char a;
        int step;
        cin>>a>>step;

        if(a=='U'){
            y+=step;
        }else if(a=='D'){
            y-=step;
        }else if(a=='R'){
            x+=step;
        }else{
            x-=step;
        }

        string pos = to_string(x) + "$" + to_string(y);
        if(s.find(pos)!=s.end()){
            break;
        }
        s.insert(pos);

    }

    int ans = abs(0-x) + abs(0-y);
    cout<<ans;
}