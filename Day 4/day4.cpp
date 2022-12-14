#include <fstream>
#include <string>
#include <iostream>
#include <tuple>
using namespace std;

bool rangeContain(int l1, int r1, int l2, int r2)
{
    return (l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2);
}

bool rangeOverlap(int l1, int r1, int l2, int r2)
{
    if (r1 < l2 || r2 < l1)
        return false;
    return true;
}

// input is guaranteed to be splitted into 2 substrings
tuple<string, string> split(const string &s, const char delim)
{
    int deliIdx = s.find(delim);
    return make_tuple(s.substr(0, deliIdx), s.substr(deliIdx + 1, string::npos));
}

int main()
{
    fstream inputFile("day4.input.txt");
    string line;
    int p1 = 0, p2 = 0;
    while (getline(inputFile, line))
    {
        auto [fRn, sRn] = split(line, ',');
        auto [fL, fR] = split(fRn, '-');
        auto [sL, sR] = split(sRn, '-');

        p1 += rangeContain(stoi(fL), stoi(fR), stoi(sL), stoi(sR));

        p2 += rangeOverlap(stoi(fL), stoi(fR), stoi(sL), stoi(sR));
    }
    cout << p1 << endl;
    cout << p2;
}