#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

tuple<int, int, int> assignMax(int max1, int max2, int max3, int val)
{
    if (val >= max1)
    {
        max3 = max2;
        max2 = max1;
        max1 = val;
    }
    else if (val >= max2)
    {
        max3 = max2;
        max2 = val;
    }
    else if (val >= max3)
        max3 = val;

    return make_tuple(max1, max2, max3);
}

int main()
{
    fstream inputFile("day1.input.txt");
    string line;
    int max1 = 0, max2 = 0, max3 = 0, curr = 0;
    while (getline(inputFile, line))
    {
        if (line.find_first_not_of(' ') != string::npos)
        {
            curr += stoi(line);
        }
        else
        {
            tie(max1, max2, max3) = assignMax(max1, max2, max3, curr);
            curr = 0;
        }
    }
    tie(max1, max2, max3) = assignMax(max1, max2, max3, curr);

    // Part 1
    cout << max1 << endl;

    // Part 2
    cout << max1 + max2 + max3;
}