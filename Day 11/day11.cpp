#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <functional>
#include <math.h>
#define ll unsigned long long
using namespace std;

struct Monkey
{
    ll id;
    queue<ll> items;
    function<ll(ll)> operation;
    ll count;
    ll div;
    ll toTrue;
    ll toFalse;
};

// Debugging purpose
void printMonkey(Monkey monkey)
{
    cout << "No. " << monkey.id << '\n'
         << "Inspections count: " << monkey.count << '\n'
         << "Divisible condition: " << monkey.div << '\n'
         << "If true: throw to No. " << monkey.toTrue << '\n'
         << "If false: throw to No. " << monkey.toFalse << '\n'
         << "All items: ";
    while (!monkey.items.empty())
    {
        cout << monkey.items.front() << ' ';
        monkey.items.pop();
    }
    cout << "\n\n";
}

int main()
{
    fstream inputFile("day11.input.txt");
    vector<Monkey> monkeys;
    string line;
    ll n = 0, lcm = 1;
    while (getline(inputFile, line))
    {
        if (line.starts_with("Monkey"))
        {
            monkeys.push_back(Monkey{n, queue<ll>(), NULL, 0, 0, 0, 0});
            n++;
        }
        else if (ll idx = line.find("Starting items"); idx != string::npos)
        {
            istringstream tokens(line.substr(idx + 16));
            string num;
            while (tokens >> num)
            {
                if (num[num.size() - 1] == ',')
                {
                    monkeys[n - 1].items.push(stoi(num.substr(0, num.size() - 1)));
                }
                else
                {
                    monkeys[n - 1].items.push(stoi(num));
                }
            }
        }
        else if (line.find("Operation") != string::npos)
        {
            istringstream tokens(line);
            string _, first, second;
            char op;
            tokens >> _ >> _ >> _ >> _ >> op >> second;
            if (second == "old")
            {
                monkeys[n - 1].operation = [](ll i) -> ll
                { return i * i; };
            }
            else
            {
                ll num = stoi(second);
                if (op == '+')
                {
                    monkeys[n - 1].operation = [num](ll i) -> ll
                    { return i + num; };
                }
                else if (op == '*')
                {
                    monkeys[n - 1].operation = [num](ll i) -> ll
                    { return i * num; };
                }
            }
        }
        else if (line.find("Test") != string::npos)
        {
            istringstream tokens(line);
            string _, divisible;
            tokens >> _ >> _ >> _ >> divisible;
            monkeys[n - 1].div = stoi(divisible);
            lcm *= monkeys[n - 1].div;
        }
        else if (line.find("true") != string::npos)
        {
            istringstream tokens(line);
            string _, t;
            tokens >> _ >> _ >> _ >> _ >> _ >> t;
            monkeys[n - 1].toTrue = stoi(t);
        }
        else if (line.find("false") != string::npos)
        {
            istringstream tokens(line);
            string _, f;
            tokens >> _ >> _ >> _ >> _ >> _ >> f;
            monkeys[n - 1].toFalse = stoi(f);
        }
    }

    for (ll _ = 0; _ < 10000; _++)
    {
        // throw
        for (auto &monkey : monkeys)
        {
            monkey.count += monkey.items.size();
            while (!monkey.items.empty())
            {
                ll item = monkey.items.front();
                monkey.items.pop();

                item = monkey.operation(item);
                item = item % lcm;

                if (item % monkey.div == 0)
                    monkeys[monkey.toTrue].items.push(item);
                else
                    monkeys[monkey.toFalse].items.push(item);
            }
        }
    }

    ll max1 = 0, max2 = 0;
    for (auto &monkey : monkeys)
    {
        if (monkey.count >= max1)
        {
            max2 = max1;
            max1 = monkey.count;
        }
        else if (monkey.count >= max2)
        {
            max2 = monkey.count;
        }
    }

    cout << max1 << ' ' << max2 << endl;
    cout << max1 * max2 << endl;
}