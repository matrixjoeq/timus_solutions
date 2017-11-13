/*
 * 1306. Sequence Median
 * Time limit: 1.0 second
 * Memory limit: 1 MB
 * Language limit: C, C++, Pascal
 *
 * [Description]
 * Given a sequence of N nonnegative integers. Let's define the median of such
 * sequence. If N is odd the median is the element with stands in the middle of
 * the sequence after it is sorted. One may notice that in this case the median
 * has position (N+1)/2 in sorted sequence if sequence elements are numbered 
 * starting with 1. If N is even then the median is the semi-sum of the two 
 * "middle" elements of sorted sequence. I.e. semi-sum of the elements in 
 * positions N/2 and (N/2)+1 of sorted sequence. But original sequence might be
 * unsorted.
 * Your task is to write program to find the median of given sequence.
 *
 * [Input]
 * The first line of input contains the only integer number N — the length of 
 * the sequence. Sequence itself follows in subsequent lines, one number in a
 * line. The length of the sequence lies in the range from 1 to 250000. Each
 * element of the sequence is a positive integer not greater than 2^31−1
 * inclusive.
 *
 * [Output]
 * You should print the value of the median with exactly one digit after 
 * decimal point.
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
#include <deque>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <iterator>
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


void handle_odd(uint32_t n)
{
    priority_queue<uint32_t, deque<uint32_t> > values;
    uint32_t index_median = (n + 1) / 2;

    for (uint32_t i = 0; i < index_median; ++i) {
        uint32_t x;
        cin >> x;
        values.push(x);
    }

    for (uint32_t i = 0; i < (n - index_median); ++i) {
        uint32_t x;
        cin >> x;
        if (x < values.top()) {
            values.pop();
            values.push(x);
        }
    }

    cout << values.top() << ".0" << endl;
}


void handle_even(uint32_t n)
{
    priority_queue<uint32_t, deque<uint32_t> > values;
    uint32_t index_median = n / 2 + 1;

    for (uint32_t i = 0; i < index_median; ++i) {
        uint32_t x;
        cin >> x;
        values.push(x);
    }

    for (uint32_t i = 0; i < (n - index_median); ++i) {
        uint32_t x;
        cin >> x;
        if (x < values.top()) {
            values.pop();
            values.push(x);
        }
    }

    uint32_t v1 = values.top();
    values.pop();
    uint32_t v2 = values.top();
    uint32_t d = (v1 + v2) / 2;
    cout << d << ((v1 + v2) % 2 ? ".5" : ".0") << endl;
}


int main()
{
    uint32_t n;
    get_single_input(n);

    if (n % 2)
        handle_odd(n);
    else
        handle_even(n);

    return 0;
}

