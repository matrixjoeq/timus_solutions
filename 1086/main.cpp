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


static vector<int> s_primes;


static bool is_prime(int n)
{
    if (find(s_primes.begin(), s_primes.end(), n) != s_primes.end()) return true;
    if (n == 0 || n == 1) return false;
    if (n % 2 == 0) {
        if (n == 2) {
            s_primes.push_back(n);
            return true;
        }
        else
            return false;
    }

    for (vector<int>::iterator it = s_primes.begin(); it != s_primes.end(); ++it) {
        if (n % *it == 0) {
            return false;
        }
    }

    s_primes.push_back(n);
    return true;
}


static void find_first_n_primes(int n)
{
    assert(is_prime(2));
    int number = 3;
    for (int i = 2; i <= n; ++i) {
        while (!is_prime(number)) number += 2;
        number += 2;
    }
}


int main()
{
    int k = 0;
    get_single_input(k);

    vector<int> v_nth;
    get_inputs(v_nth);

    int max_nth = get_max(v_nth);
    find_first_n_primes(max_nth);

    for (vector<int>::iterator it = v_nth.begin(); it != v_nth.end(); ++it) {
        cout << s_primes[*it - 1] << endl;
    }

    return 0;
}

