#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include <unordered_set>
#include <sstream>
using namespace std;

struct hashFunction
{
    size_t operator()(const pair<int, int> &x) const
    {
        return x.first ^ x.second;
    }
};

bool isTouch(int headX, int headY, int tailX, int tailY)
{
    if (tailX - 1 <= headX && headX <= tailX + 1 &&
        tailY - 1 <= headY && headY <= tailY + 1)
    {
        return true;
    }
    return false;
}

// Invoke after head moves
void tailMove(int headX, int headY, int &tailX, int &tailY)
{
    // No need to move
    if (isTouch(headX, headY, tailX, tailY))
    {
        return;
    }
    // If not same row and column, move diagonally
    if (headX != tailX && headY != tailY)
    {
        if (abs(headX - tailX) == 1)
        {
            tailX += (headX - tailX);
            tailY += (headY - tailY > 0) ? 1 : -1;
        }
        else
        {
            tailY += (headY - tailY);
            tailX += (headX - tailX > 0) ? 1 : -1;
        }
        return;
    }

    // Move towards tail
    if (tailX == headX)
        tailY += (headY - tailY > 0) ? 1 : -1;

    if (tailY == headY)
        tailX += (headX - tailX > 0) ? 1 : -1;
}

int main()
{
    fstream inputFile("day9.input.txt");
    string line;
    unordered_set<pair<int, int>, hashFunction> visitedP1, visitedP2;

    int headX = 0, headY = 0, tailX = 0, tailY = 0;

    // first row is head, the remains are tails
    // first col is x and second col is y
    int rope[10][2]{{0}};

    while (getline(inputFile, line))
    {
        istringstream tokens(line);
        char dir;
        int step;
        tokens >> dir >> step;

        for (int i = 0; i < step; i++)
        {
            if (dir == 'U')
            {
                headY++;
                rope[0][1]++;
            }
            else if (dir == 'D')
            {
                headY--;
                rope[0][1]--;
            }
            else if (dir == 'L')
            {
                headX--;
                rope[0][0]--;
            }
            else if (dir == 'R')
            {
                headX++;
                rope[0][0]++;
            }
            tailMove(headX, headY, tailX, tailY);
            visitedP1.insert(make_pair(tailX, tailY));

            for (int i = 1; i < 10; i++)
            {
                tailMove(rope[i - 1][0], rope[i - 1][1], rope[i][0], rope[i][1]);
            }
            visitedP2.insert(make_pair(rope[9][0], rope[9][1]));
        }
    }

    int p1 = visitedP1.size(), p2 = visitedP2.size();
    cout << p1 << endl;
    cout << p2;
}