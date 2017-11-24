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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>

using namespace std;

struct CityStatistic
{
    CityStatistic() : id(0), stat(0) {}
    CityStatistic(uint32_t id_, uint32_t stat_) : id(id_), stat(stat_) {}
    CityStatistic(const CityStatistic& other)
        : id(other.id), stat(other.stat)
    {}

    CityStatistic& operator=(const CityStatistic& other)
    {
        if (this != &other)
        {
            id = other.id;
            stat = other.stat;
        }
        return *this;
    }

    bool operator<(const CityStatistic& other) const
    {
        return stat < other.stat;
    }

    uint32_t id;
    uint32_t stat;
};

// Get a single input from stdin
template<typename T>
static inline void get_single_input(T& x)
{
    string line;
    getline(cin, line);
    istringstream input(line);
    input >> x;
}

// Get all lines input from stdin
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

// Get one line input from stdin
// Add the values as elements in container
template<typename Container>
static void get_line_input(Container& c)
{
    typedef typename Container::value_type T;

    string line;
    getline(cin, line);
    istringstream input(line);
    T x;
    while (input >> x)
    {
        c.push_back(x);
    }
}

static inline void get_single_uint(uint32_t& x)
{
    scanf("%u", &x);
}

template<typename ForwardIterator>
static void get_n_uint(uint32_t n, ForwardIterator i)
{
    uint32_t x;
    while (n--)
    {
        get_single_uint(x);
        *i++ = x;
    }
}

typedef vector<CityStatistic> DataMap;
typedef typename DataMap::value_type DataValue;
typedef typename DataMap::iterator DataMapIter;

static void setup_statistics(DataMap& m, uint32_t n)
{
    m.reserve(n);
    uint32_t x;
    for (uint32_t i = 1; i <= n; ++i)
    {
        get_single_uint(x);
        CityStatistic cs(i, x);
        m.push_back(cs);
    }

    printf("origin data\n");
    for (DataMapIter it = m.begin(); it != m.end(); ++it)
    {
        printf("c: %u, s: %u\n", it->id, it->stat);
    }

    make_heap(m.begin(), m.end());
    sort_heap(m.begin(), m.end());
    
    printf("sorted data\n");
    for (DataMapIter it = m.begin(); it != m.end(); ++it)
    {
        printf("c: %u, s: %u\n", it->id, it->stat);
    }
}

static int query(DataMap& m, uint32_t l, uint32_t r, uint32_t x)
{
    printf("query: %u\n", x);
    CityStatistic cs(0, x);
    DataMapIter bound = lower_bound(m.begin(), m.end(), cs);
    if (bound == m.end())
    {
        printf("no lower bound found\n");
        return 0;
    }
    else 
    {
        printf("lower bound: %u %u\n", bound->id, bound->stat);
        while (bound->stat == x)
        {
            if (bound->id >= l && bound->id <= r)
                return 1;
            ++bound;
        }

        return 0;
    }
}

template<typename Container>
static void make_query(DataMap& m, Container& data, uint32_t q)
{
    typedef typename Container::value_type T;
    typedef typename Container::iterator DataIter;

    DataIter it = data.begin();
    while (q--)
    {
        uint32_t l = *it++;
        uint32_t r = *it++;
        uint32_t x = *it++;
        cout << query(m, l, r, x);
    }
    cout << endl;
}

int main()
{
    uint32_t n;
    get_single_uint(n);

    vector<CityStatistic> data_map;
    setup_statistics(data_map, n);
       
    uint32_t q;
    get_single_uint(q);
    printf("q: %u\n", q);

    vector<uint32_t> query_data(q * 3);
    for (vector<uint32_t>::iterator it = query_data.begin(); it != query_data.end(); ++it)
    {
        uint32_t x;
        get_single_uint(x);
        printf("x: %u\n");
        *it = x;
    }

    vector<uint32_t>::iterator it = query_data.begin();
    while (it != query_data.end());
    {
        printf("%u %u %u\n", *it++, *it++, *it++);
    }

    make_query(data_map, query_data, q);

    return 0;
}

