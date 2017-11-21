/*
 * 1613. For Fans of Statistics
 * Time limit: 1.0 second
 * Memory limit: 64 MB
 *
 * [Description]
 * Have you ever thought about how many people are transported by trams every 
 * year in a city with a ten-million population where one in three citizens 
 * uses tram twice a day?
 * Assume that there are n cities with trams on the planet Earth. Statisticians
 * counted for each of them the number of people transported by trams during 
 * last year. They compiled a table, in which cities were sorted alphabetically.
 * Since city names were inessential for statistics, they were later replaced 
 * by numbers from 1 to n. A search engine that works with these data must be 
 * able to answer quickly a query of the following type: is there among the 
 * cities with numbers from l to r such that the trams of this city transported
 * exactly x people during last year. You must implement this module of the system.
 *
 * [Input]
 * The first line contains the integer n, 0 < n < 70000. The second line contains
 * statistic data in the form of a list of integers separated with a space. In 
 * this list, the ith number is the number of people transported by trams of the
 * ith city during last year. All numbers in the list are positive and do not 
 * exceed 10^9 − 1. In the third line, the number of queries q is given, 
 * 0 < q < 70000. The next q lines contain the queries. Each of them is a triple 
 * of integers l, r, and x separated with a space; 1 ≤ l ≤ r ≤ n; 0 < x < 10^9.
 *
 * [Output]
 * Output a string of length q in which the ith symbol is “1” if the answer to 
 * the ith query is affirmative, and “0” otherwise.
 */

#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cmath>

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

using namespace std;

// Get a single input from stdin
template<typename T>
static void get_single_input(T& x)
{
    cin >> x;
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

