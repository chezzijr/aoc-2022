#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// return result points
int rps(int opponent, int self)
{
    // rock = 0, paper = 1, scissors = 2

    // draw
    if (opponent == self)
    {
        return 3;
    }

    // lose
    if (opponent - self == 1 || opponent - self == -2)
    {
        return 0;
    }

    return 6;
}

// return move
int revrps(int opponent, int result)
{
    // rock = 0, paper = 1, scissors = 2
    // lose = 0, draw = 1, win = 2
    // return the total points according to the move and the result

    int self, score;
    if (result == 2)
    {
        score = 6;
        self = (opponent + 1) % 3;
    }

    if (result == 1)
    {
        score = 3;
        self = opponent;
    }

    if (result == 0)
    {
        score = 0;
        self = opponent - 1;
        self = self < 0 ? self + 3 : self;
    }

    return score + self + 1;
}

int main()
{
    fstream inputFile("day2.input.txt");
    string line;
    int p1 = 0, p2;

    while (getline(inputFile, line))
    {
        istringstream tokens(line);
        char o, s;
        tokens >> o >> s;
        p1 += rps(o - 'A', s - 'X') + (s - 'X' + 1);
        p2 += revrps(o - 'A', s - 'X');
    }

    cout << p1 << endl;
    cout << p2;
}