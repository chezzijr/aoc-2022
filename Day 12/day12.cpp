#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#define endl '\n'
using namespace std;

int main()
{
    fstream inputFile("day12.input.txt");
    vector<string> lines;
    lines.reserve(40);
    string line;
    int col = 0;
    int sCol, sRow, eCol, eRow;
    while (getline(inputFile, line))
    {
        if (!col)
        {
            col = line.size();
        }
        if (auto p = line.find('S'); p != string::npos)
        {
            sCol = p;
            sRow = lines.size();
        }
        if (auto p = line.find('E'); p != string::npos)
        {
            eCol = p;
            eRow = lines.size();
        }

        lines.push_back(line);
    }
    int row = lines.size();
    lines[eRow][eCol] = 'z';
    lines[sRow][sCol] = 'a';

    // TODO!
    // BFS
    auto validPos = [&row, &col](int r, int c)
    {
        return 0 <= r && r < row && 0 <= c && c < col;
    };

    auto moveable = [&validPos, &lines](int r, int c, int nr, int nc)
    {
        return validPos(nr, nc) && (lines[r][c] - lines[nr][nc] <= 1);
    };

    int visited[100][100]{{}};
    visited[eRow][eCol] = 1;

    queue<pair<int, int>> q;
    q.push(make_pair(eRow, eCol));

    vector<pair<int, int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    while (!visited[sRow][sCol] && !q.empty())
    {
        auto [r, c] = q.front();
        q.pop();

        for (auto &[dr, dc] : dir)
        {
            // TODO
            int nr = r + dr, nc = c + dc;
            if (moveable(r, c, nr, nc))
            {
                if (!visited[nr][nc] || visited[nr][nc] > visited[r][c] + 1)
                {
                    visited[nr][nc] = visited[r][c] + 1;
                    q.push(make_pair(nr, nc));
                }
            }
        }
    }

    // PART 1
    cout << visited[sRow][sCol] - 1 << endl;

    // PART 2
    int smallest = visited[sRow][sCol];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (lines[i][j] == 'a' && visited[i][j] != 0)
                smallest = min(smallest, visited[i][j]);
        }
    }
    cout << smallest - 1;
}