#include <fstream>
#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

int main()
{
    fstream inputFile("day5.input.txt");
    string line;
    int n = 0;
    vector<deque<char>> st1, st2;
    string p1, p2;
    while (getline(inputFile, line))
    {
        if (!n)
        {
            // Each stack contains 3 characters, 2 opening and closing brackets, and 1 uppercase alphabet
            // Between every 2 stacks is a space charater
            // The number of characters in a line with n stacks of crates is 3n + (n - 1) = 4n - 1
            // line.size() = 4n - 1 => n = (line.size() + 1) / 4
            n = (line.size() + 1) / 4;
            st1.reserve(n);
            for (int i = 0; i < n; i++)
                st1.emplace_back(deque<char>());
            st2.reserve(n);
            for (int i = 0; i < n; i++)
                st2.emplace_back(deque<char>());
        }

        if (line.starts_with("move"))
        {
            istringstream token(line);
            string num, from, to, _;
            token >> _ >> num >> _ >> from >> _ >> to;
            int nm = stoi(num), f = stoi(from), t = stoi(to);

            // For part 2
            // Using stack instead of deque for comprehension
            stack<char> temp;

            while (nm--)
            {
                // Part 1, which is to move 1 crate at a time
                char crate = st1[f - 1].front();
                st1[f - 1].pop_front();
                st1[t - 1].push_front(crate);

                // Part 2, can move multiple crates at once
                // Using the stack to store top n crates
                temp.push(st2[f - 1].front());
                st2[f - 1].pop_front();
            }

            while (!temp.empty())
            {
                char crate = temp.top();
                temp.pop();
                st2[t - 1].push_front(crate);
            }
        }
        else if (line.find_first_not_of(' ') != string::npos)
        {
            for (int i = 0; i < n; i++)
            {
                int idx = i * 4 + 1;
                if ('A' <= line[idx] && line[idx] <= 'Z')
                {
                    st1[i].push_back(line[idx]);
                    st2[i].push_back(line[idx]);
                }
            }
        }
    }

    p1.reserve(n);
    p2.reserve(n);

    for (int i = 0; i < n; i++)
    {
        p1.push_back(st1[i].front());
        p2.push_back(st2[i].front());
    }

    cout << p1 << endl;
    cout << p2;
}