#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

bool check(int cycle)
{
    return 20 <= cycle && cycle % 40 == 20;
}

int main()
{
    // It is guaranteed that there is no data race
    fstream inputFile("day10.input.txt");
    string line;
    int cycle = 1, x = 1, p1 = 0;
    char CRT[240];
    while (getline(inputFile, line))
    {
        if (cycle <= 240)
        {

            if (line.starts_with("addx"))
            {
                istringstream tokens(line);
                string _;
                int val;
                tokens >> _ >> val;

                int tmp = (cycle - 1) % 40;
                CRT[cycle - 1] = (x - 1 <= tmp && tmp <= x + 1) ? '#' : '.';
                cycle++;
                p1 += x * cycle * check(cycle);

                tmp = (cycle - 1) % 40;
                CRT[cycle - 1] = (x - 1 <= tmp && tmp <= x + 1) ? '#' : '.';
                cycle++;
                x += val;
                p1 += x * cycle * check(cycle);
            }
            else
            {
                int tmp = (cycle - 1) % 40;
                CRT[cycle - 1] = (x - 1 <= tmp && tmp <= x + 1) ? '#' : '.';
                cycle++;
                p1 += x * cycle * check(cycle);
            }
        }
    }

    cout << p1 << endl;

    for (int i = 1; i <= 240; i++)
    {
        cout << CRT[i - 1];
        if (i % 40 == 0)
            cout << endl;
    }
}