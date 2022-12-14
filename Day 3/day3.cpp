#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// input is guaranteed to be in between a-z or A-Z
int charToIndex(char chr)
{
    if ('A' <= chr && chr <= 'Z')
    {
        return chr - 'A' + 26;
    }
    return chr - 'a';
}

int main()
{
    fstream inputFile("day3.input.txt");
    string line;
    int p1 = 0, p2 = 0, k = 0;
    int charFreqP2[52]{};
    while (getline(inputFile, line))
    {
        bool charFreqP1[52]{};
        for (int i = 0; i < line.size() / 2; i++)
        {
            int idx = charToIndex(line[i]);
            charFreqP1[idx] = true;
            if (charFreqP2[idx] == k)
            {
                charFreqP2[idx] = k + 1;
            }
        }

        for (int i = line.size() / 2; i < line.size(); i++)
        {
            int idx = charToIndex(line[i]);
            if (charFreqP1[idx])
            {
                p1 += idx + 1;
                charFreqP1[idx] = false;
            }
            if (charFreqP2[idx] == k)
            {
                charFreqP2[idx] = k + 1;
            }
        }

        if (k == 2)
        {
            for (int i = 0; i < 52; i++)
            {
                if (charFreqP2[i] == 3)
                {
                    p2 += i + 1;
                }
                charFreqP2[i] = 0;
            }
        }

        k = (k + 1) % 3;
    }
    cout << p1 << endl;
    cout << p2;
}