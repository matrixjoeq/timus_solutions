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
     // TODO
     return 0;
}

// the 15000th prime number is 163841
static bool s_numbers[163841 + 1]; // [0, x]
static vector<int> s_primes;
#define ARRAY_LENGTH(x) (sizeof((x)) / sizeof((x)[0]))

static int get_next_prime(int p)
{
    for (int i = p + 1; i < ARRAY_LENGTH(s_numbers); ++i) {
        if (s_numbers[i]) return i;
    }

    return -1;
}


static void pick_prime_numbers(int x)
{
    x = ARRAY_LENGTH(s_numbers) - 1;
    memset(s_numbers, 1, sizeof(s_numbers));
    s_numbers[0] = false;
    s_numbers[1] = false;
    
    int p = 1;
    while (((p = get_next_prime(p)) != -1) && (p * p <= x)) {
        for (int i = p + 1; i <= x; ++i) {
            if (i % p == 0) s_numbers[i] = false;
        }
    }

    for (int i = 2; i <= x; ++i) {
        if (s_numbers[i]) s_primes.push_back(i);
    }
}


int main()
{
    int k;
    get_single_input(k);

    vector<int> v_nth;
    get_inputs(v_nth);

    pick_prime_numbers(0);
    for (vector<int>::iterator it = v_nth.begin(); it != v_nth.end(); ++it) {
        cout << s_primes[*it - 1] << endl;
    }

    return 0;
}

