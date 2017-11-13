/*
 * 1126. Magnetic Storms
 * Time limit: 0.5 second
 * Memory limit: 64 MB
 *
 * [Description]
 * The directory of our kindergarten decided to be attentive to the children's
 * health and not to let them walk outdoors during magnetic storms. Special 
 * devices that measure and display magnetic intensity were ordered. If the
 * readout exceeded some certain level the children were told to go indoors. 
 * They disliked it because they couldn't play their games up to the end. The 
 * nannies hated it because they had to dress and undress children many times.
 * After a while it became clear that one could try to forecast magnetic 
 * intensity because long periods of quietude alternated with short periods of
 * plenty of sharp peaks (this is called a magnetic storm). Hence a new 
 * modification of the devices was ordered.
 * The new devices were to remember the situation within several last hours and
 * to display the maximal intensity during the period. If the intensity was low
 * within the last 6 hours the magnetic field was regarded to be quiet; the 
 * children were let outdoors and played all the prescript time. Otherwise new
 * peaks were probable and the children spent their time indoors.
 * Your task is to write a program for a new version of the device. As a matter
 * of fact you are to solve just the main problem of modification. All the rest
 * is already done.
 * You are given a number M which is length of a period (in seconds) within which
 * peaks are to be stored and displayed. A sequence of measured magnetic intensity
 * values is given to you as well. Each measurement is a number within the range
 * from 0 to 100000.
 * Your are to output a sequence of values displayed by the device. The first
 * number of the sequence is the maximal element of the first M input numbers,
 * the second number is the maximal element of the 2nd, …, M+1-st input numbers
 * and so on.
 * We hope that the new devices with your program won't go back on nannies and 
 * children will not walk during magnetic storms.
 *
 * [Input]
 * The first line contains a number M, 2 ≤ M ≤ 14000. Then values (N integers)
 * measured by the device follow each one in its line. There is a number −1 in
 * the end. M ≤ N ≤ 25000.
 *
 * [Output]
 * a sequence of readouts, each one in its line.
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


template<typename Iterator>
static typename iterator_traits<Iterator>::value_type
get_max(Iterator first, Iterator last)
{
    typename iterator_traits<Iterator>::value_type x = *first;
    for (Iterator it = first; it != last; ++it) {
        if (*it > x) {
            x = *it;
        }
    }

    return x;
}


int main()
{
    int m;
    get_single_input(m);

    vector<int> values;
    get_inputs(values);
    vector<int>::iterator it_first = values.begin();
    vector<int>::iterator it_last = it_first + m;

    int peak = get_max(it_first, it_last);
    do {
        cout << peak << endl;
        int v_pop = *it_first;
        int v_push = *it_last;
        if (v_push != -1) {
            if (v_push > peak)
                peak = v_push;
            else if (v_pop == peak) {
                peak = get_max(it_first + 1, it_last + 1);
            }
        }
        ++it_first;
        ++it_last;
    } while (it_last != values.end());

    return 0;
}

