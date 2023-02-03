#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
#define PLAYER '0'
#define CRATE '1'
#define ENDPOINT '2'
#define WALL '/'
#define ROAD '-'

pair<int, int> playerSite;
vector<pair<int, int>> endPointsSite;
vector<vector<char>> mMap;
enum Direction
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};
const map<char, int> dirChar{
    {'w', UP}, {'W', UP}, 
    {'s', DOWN}, {'S', DOWN}, 
    {'a', LEFT}, {'A', LEFT}, 
    {'d', RIGHT}, {'D', RIGHT}
};
const int direct[]{0, 1, 0, -1, 0};

void init();
void run();
void render(vector<vector<char>>);
bool isWin();
bool input();
bool isValid(int);

void init()
{
    cout << "Please enter filename.(without .txt)" << endl;
    string filename;
    cin >> filename;
    fstream input(filename + ".txt", ios::in);
    int n, m;
    input >> n >> m;
    mMap.resize(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            input >> mMap[i][j];
            if (mMap[i][j] == PLAYER)
                playerSite = {i, j};
            if (mMap[i][j] == ENDPOINT)
                endPointsSite.push_back({i, j});
            if (mMap[i][j] == PLAYER || mMap[i][j] == ENDPOINT)
                mMap[i][j] = ROAD;
        }
    input.close();
}

void run()
{
    render(mMap);
    while (!isWin())
        if (input())
            render(mMap);
}

bool input()
{
    char c = getch();
    if (dirChar.find(c) != dirChar.end())
        return isValid(dirChar.at(c));
    return false;
}

void render(vector<vector<char>> tmp)
{
    system("cls");
    for (auto &i : endPointsSite)
        tmp[i.first][i.second] = tmp[i.first][i.second] != CRATE ? ENDPOINT : CRATE;
    tmp[playerSite.first][playerSite.second] = PLAYER;
    for (auto &i : tmp)
    {
        for (auto &j : i)
            cout << j;
        cout << endl;
    }
}

bool isValid(int dir)
{
    int x = playerSite.first + direct[dir], y = playerSite.second + direct[dir + 1], nextX = x + direct[dir], nextY = y + direct[dir + 1];
    if (mMap[x][y] == ROAD)
    {
        playerSite = {x, y};
        return true;
    }
    if (mMap[x][y] == CRATE && mMap[nextX][nextY] == ROAD)
    {
        swap(mMap[x][y], mMap[nextX][nextY]);
        playerSite = {x, y};
        return true;
    }
    return false;
}

bool isWin()
{
    bool result = true;
    for (auto &i : endPointsSite)
        result &= (mMap[i.first][i.second] == CRATE);
    return result;
}

int main()
{
    init();
    run();
    return 0;
}