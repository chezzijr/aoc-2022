#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int part1(const string &line)
{
    int p1 = 0;

    // Part 1
    for (int i = 3; i < line.size(); i++)
    {
        if (
            line[i] != line[i - 1] &&
            line[i] != line[i - 2] &&
            line[i] != line[i - 3] &&
            line[i - 1] != line[i - 2] &&
            line[i - 1] != line[i - 3] &&
            line[i - 2] != line[i - 3])
        {
            p1 = i + 1;
            break;
        }
    }

    return p1;
}

int part2(const string &line)
{
    int p2 = 0, cnt = 0, k = 14;
    int arr[26]{};
    for (int i = 0; i < 14; i++)
    {
        int idx = line[i] - 'a';
        if (arr[idx] == 0)
        {
            cnt++;
        }
        arr[idx]++;
    }

    while (cnt < 14)
    {
        int i1 = line[k] - 'a', i2 = line[k - 14] - 'a';
        if (arr[i1] == 0)
        {
            cnt++;
        }
        arr[i1]++;
        arr[i2]--;
        if (arr[i2] == 0)
            cnt--;
        k++;
    }

    return k;
}

int main()
{
    string line;
    getline(fstream("day6.input.txt"), line);

    cout << part1(line) << endl;
    cout << part2(line);
}