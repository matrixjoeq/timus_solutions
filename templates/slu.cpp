/*
[Description]
[Input]
[Output]
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>

#include <limits>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Get a single input from stdin
template<typename T>
static void get_single_input(T& x)
{
    string line;
    getline(cin, line);
    istringstream input(line);
    input >> x;
}

// Get a line input from stdin
// Add the values as elements in Container
template<typename Container>
static void get_inputs(Container& c)
{
    typedef typename Container::value_type T;

    string line;
    while (getline(cin, line)) {
        istringstream input(line);

        T x;
        while (input >> x) {
            c.push_back(x);
        }
    }
}

int main()
{
    return 0;
}

