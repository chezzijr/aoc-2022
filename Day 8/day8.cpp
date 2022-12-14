#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> inputArr;
int n = 0;
int part1()
{
    vector<vector<int>> visible;
    visible.reserve(n);
    for (int i = 0; i < n; i++)
    {
        visible.emplace_back(vector<int>(n, 0));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i == 0 || j == 0) || (i == n - 1 || j == n - 1))
                visible[i][j] = 1;
        }
    }

    // left to right
    for (int i = 1; i < n - 1; i++)
    {
        int maxRow = inputArr[i][0];
        for (int j = 1; j < n - 1; j++)
        {
            if (inputArr[i][j] > maxRow)
            {
                maxRow = inputArr[i][j];
                visible[i][j] = 1;
            }
        }
    }

    // right to left
    for (int i = 1; i < n - 1; i++)
    {
        int maxRow = inputArr[i][n - 1];
        for (int j = n - 2; j > 0; j--)
        {
            if (inputArr[i][j] > maxRow)
            {
                maxRow = inputArr[i][j];
                visible[i][j] = 1;
            }
        }
    }

    // top down
    for (int j = 1; j < n - 1; j++)
    {
        int maxCol = inputArr[0][j];
        for (int i = 1; i < n - 1; i++)
        {
            if (inputArr[i][j] > maxCol)
            {
                maxCol = inputArr[i][j];
                visible[i][j] = 1;
            }
        }
    }

    // bottom up
    for (int j = 1; j < n - 1; j++)
    {
        int maxCol = inputArr[n - 1][j];
        for (int i = n - 2; i > 0; i--)
        {
            if (inputArr[i][j] > maxCol)
            {
                maxCol = inputArr[i][j];
                visible[i][j] = 1;
            }
        }
    }

    int s = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visible[i][j])
            {
                s++;
            }
        }
    }

    return s;
}

int look(int i, int j, int dx, int dy)
{
    int currVal = inputArr[i][j];
    int s = 0;
    while (i > 0 && j > 0 && i < n - 1 && j < n - 1)
    {
        i += dy;
        j += dx;
        s++;
        if (inputArr[i][j] >= currVal)
            break;
    }

    return s;
}

int part2()
{
    vector<vector<int>> res;
    res.reserve(n);
    for (int i = 0; i < n; i++)
    {
        res.emplace_back(vector<int>(n, 0));
    }

    int mx = 0;

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < n - 1; j++)
        {
            res[i][j] =
                look(i, j, -1, 0) * look(i, j, 1, 0) * look(i, j, 0, -1) * look(i, j, 0, 1);
            mx = max(mx, res[i][j]);
        }
    }

    return mx;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    fstream input("day8.input.txt");
    string line;

    int k = 0;
    while (getline(input, line))
    {
        if (!n)
        {
            n = line.size();
            inputArr.reserve(n);
            for (int i = 0; i < n; i++)
            {
                inputArr.emplace_back(vector<int>(n, 0));
            }
        }
        for (int i = 0; i < n; i++)
        {
            inputArr[k][i] = line[i] - '0';
        }
        k += 1;
    }

    cout << part1() << endl;
    cout << part2();
}