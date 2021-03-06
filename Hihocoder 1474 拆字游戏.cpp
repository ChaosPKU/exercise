/*
描述
小Kui喜欢把别人的名字拆开来，比如“螺”就可以拆成“虫田糸”，小Kui的语文学的不是很好，于是她决定使用编程的方式来解决这个问题。

给出一个01矩阵，1占据的部分即为需要拆的字，如果两个1分享一条边，那么它们连通。连通具有传递性，即如果a、b连通，b、c连通，则a、c连通。

连通的一系列1被看做可以拆出的一块，现在小Kui需要输出这些拆出的块（用一个01矩阵表示，并且要求矩阵的大小尽可能的小）。

为了确保输出的顺序尽可能的和书写的顺序一致，小Kui从每个块中选出最左上角的点（最左侧的点中，最靠上的）作为代表点，然后按照代表点从左到右（若相同则按从上到下）的顺序输出所有拆出的块。

输入
输入的第一行为两个正整数N、M，表示01矩阵的大小。

接下来N行，每行M个01字符，描述一个需要拆的字。

对于40%的数据，满足1<=N,M<=10。

对于100%的数据，满足1<=N,M<=500。

输出
按照代表点从左到右（若相同则按从上到下）的顺序输出所有拆出的块。

对于每个块，先输出其大小，然后用对应的01矩阵表示这个块。

额外的样例
样例输入
11 17
00000000000000000
00001111111100000
00000000000000000
00111111111111100
00000000100000000
00000010101110000
00000110100011000
00011100100001000
00000010100000000
00000001100000000
00000000000000000
样例输出
7 13
1111111111111
0000001000000
0000001000000
0000001000000
0000001000000
0000001000000
0000011000000
3 4
0001
0011
1110
1 8
11111111
1 1
1
3 4
1110
0011
0001


样例输入
14 22
0000000000001111111100
0000000000001101101100
0000110000001111111100
0000110000001101101100
0111111110001111111100
0110110110000000000000
0110110110000011000000
0111111110001111111000
0000110000000001100000
0000110110001111111100
0111111111000111111000
0000000010001101101100
0000000000000001100000
0000000000000011100000
样例输出
10 9
000110000
000110000
111111110
110110110
110110110
111111110
000110000
000110110
111111111
000000010
5 8
11111111
11011011
11111111
11011011
11111111
8 8
00110000
11111110
00011000
11111111
01111110
11011011
00011000
00111000
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int N, M;
int dir[5] = {0, 1, 0, -1, 0};

void DFS(vector<vector<int>> &grid, vector<int> &border, int &tag, int x, int y){
    if(x < 0 || y < 0 || x >= N || y >= M || grid[x][y] != 1)
        return;
    grid[x][y] = tag;
    border[0] = min(border[0], x);
    border[1] = max(border[1], x);
    border[2] = min(border[2], y);
    border[3] = max(border[3], y);
    for(int i = 0;i < 4; ++ i)
        DFS(grid, border, tag, x + dir[i], y + dir[i + 1]);
}

void print(const vector<vector<int>> &grid, const vector<int> &border, const int &tag){
    cout << border[1] - border[0] + 1 << " " << border[3] - border[2] + 1 << endl;
    for(int i = border[0];i <= border[1]; ++ i){
        for(int j = border[2]; j <= border[3]; ++ j)
            if(grid[i][j] == tag) cout << "1";
            else cout << "0";
        cout << endl;
    }
}

int main(){
    int x, y, i, j, tag;
    char C;
    cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M, 0));
    for(i = 0;i < N; ++ i)
        for(j = 0;j < M; ++ j){
            cin >> C;
            grid[i][j] = C - '0';
        }
    vector<int> border(4, 0);
    tag = 1;
    for(y = 0; y < M; ++ y)
        for(x = 0; x < N; ++ x)
            if(grid[x][y] == 1){
                border[1] = border[3] = -1;
                border[0] = border[2] = 505;
                DFS(grid, border, ++ tag, x, y);
                print(grid, border, tag);
            }
    return 0;
}
