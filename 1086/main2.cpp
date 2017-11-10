/*
 * [Description]
 *
 * [Input]
 *
 * [Output]
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <cassert>

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


template<typename Container>
static typename Container::value_type get_max(Container& c)
{
    typedef typename Container::value_type T;
    typedef typename Container::iterator Iter;

    T x;
    for (Iter it = c.begin(); it != c.end(); ++it) {
        if (*it > x) {
            x = *it;
        }
    }

    return x;
}


// according to prime number theorem
// the number of prime numbers in range [0, x] is about x/ln(x)
// considering the estimation deviation no larger than 15%
// we can guess the range if the requirement is to find first n
// prime numbers
static int guess_range(int n)
{
    int r = 2;
    while (r / log1p(r - 1) < n) ++r;
    return static_cast<int>(r * 1.15);
}


static int get_next_prime(int p, bool* p_numbers, size_t size)
{
    for (int i = p + 1; i < size; ++i) {
        if (*(p_numbers + i)) return i;
    }

    return -1;
}


static void pick_prime_numbers(int x, vector<int>& v_primes)
{
    bool* p_numbers = new bool[x + 1];
    memset(p_numbers, 1, sizeof(bool) * (x + 1));

    bool* p_n = p_numbers;
    *p_n++ = false; // set 0 to false
    *p_n++ = false; // set 1 to false
    
    int p = 1;
    while (((p = get_next_prime(p, p_numbers, x + 1)) != -1) && (p * p <= x)) {
        for (int i = p + 1; i <= x; ++i) {
            if (i % p == 0) *(p_numbers + i) = false;
        }
    }

    for (p_n = p_numbers + 2; p_n <= p_numbers + x; ++p_n) {
        if (*p_n) {
            int prime = static_cast<int>(p_n - p_numbers);
            v_primes.push_back(prime);
        }
    }

    delete[] p_numbers;
}


int main()
{
    int k;
    get_single_input(k);

    vector<int> v_nth;
    get_inputs(v_nth);

    int max_nth = get_max(v_nth);
    int range_x = guess_range(max_nth);

    vector<int> v_primes;
    v_primes.reserve(range_x / log1p(range_x - 1));
    pick_prime_numbers(range_x, v_primes);
    for (vector<int>::iterator it = v_nth.begin(); it != v_nth.end(); ++it) {
        cout << v_primes[*it - 1] << endl;
    }

    return 0;
}

