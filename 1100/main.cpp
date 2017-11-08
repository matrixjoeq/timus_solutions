/*
 * 1100. Final Standings
 * Time limit: 1.0 second
 * Memory limit: 16 MB
 *
 * [Description]
 * Old contest software uses bubble sort for generating final standings.
 * But now, there are too many teams and that software works too slow.
 * You are asked to write a program, which generates exactly the same final
 * standings as old software, but fast.
 *
 * [Input]
 * The first line of input contains only integer 1 < N ≤ 150000 — number of
 * teams. Each of the next N lines contains two integers 1 ≤ ID ≤ 10^7 and
 * 0 ≤ M ≤ 100. ID — unique number of team, M — number of solved problems.
 *
 * [Output]
 * Output should contain N lines with two integers ID and M on each. Lines
 * should be sorted by M in descending order as produced by bubble sort
 * (see below).
 *
 * [Notes]
 * Bubble sort works following way: 
 * while (exists A[i] and A[i+1] such as A[i] < A[i+1]) do
 *    Swap(A[i], A[i+1]);
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
        //cout << line;
        istringstream input(line);

        T x;
        while (input >> x) {
            c.push_back(x);
        }
    }
}

struct TeamScore
{
    int id;
    int score;

    TeamScore() : id(0), score(0) {}
    TeamScore(int id_, int score_)
      : id(id_), score(score_)
    {}
    TeamScore(const TeamScore& other)
      : id(other.id), score(other.score)
    {}

    TeamScore& operator=(const TeamScore& other)
    {
        id = other.id;
        score = other.score;
        return *this;
    }

    bool operator<(const TeamScore& other) const
    {
        return score < other.score;
    }

    bool operator>(const TeamScore& other) const
    {
        return score > other.score;
    }
};

int main()
{
    // stable_sort is a little bit more effecient than list::sort
    // so use vector for TeamScore.
    typedef vector<TeamScore> TeamScoreContainer;

    int n;
    TeamScoreContainer c;

    get_single_input(n);

    vector<int> args;
    get_inputs(args);
    
    for (int i = 0; i < n; ++i) {
        c.push_back(TeamScore(args[i * 2], args[i * 2 + 1]));
    }

    // Since bubble sort is a stable sort, we need a sorting algorithm which is 
    // also stable. list::sort is stable, stable_sort is also stable.
    //c.sort(greater<TeamScore>());
    stable_sort(c.begin(), c.end(), greater<TeamScore>());
    
    for (TeamScoreContainer::iterator it = c.begin(); it != c.end(); ++it) {
        cout << it->id << ' ' << it->score << endl;
    }

    return 0;
}

