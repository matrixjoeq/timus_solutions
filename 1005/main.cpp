#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef abs
#define abs(x) ((x) < 0 ? (-x) : (x))
#endif

int* get_inputs(int n)
{
    int* inputs = new int[n];
    int* p = inputs;
    std::string line;

    while (n > 0) {
        std::cin >> line;
        const char* pline = line.c_str();
        *p++ = atoi(pline);
        --n;
    }
    
    return inputs;
}

void get_combinations(int* weights, int n, std::vector<int>& comb)
{
    int m = 1 << n;
    for (int mask = 1; mask <= m; ++mask) {
        int v = 0;
        for (int i = 0; i < n; ++i) {
            if ((1 << i) & mask) {
                v += *(weights + i);
            }
        }
        comb.push_back(v);
    }
    std::sort(comb.begin(), comb.end());
    std::vector<int>::iterator last = std::unique(comb.begin(), comb.end());
    comb.erase(last, comb.end());
}

/*
 * At first, I though about greedy method to get the answer.
 * However, greedy way does not always give me the best answer when all stones
 * are counted. It may give a partial optimal solution and a close answer in 
 * the end. But not THE optimal solution.
 * So, at last, I decide to use brute force method to get all the possible answers.
 * Although accepted, this seems not the best way.
 */
int main()
{
    int n = 0;
    std::cin >> n;

    int* weights = get_inputs(n);
    std::vector<int> comb;
    get_combinations(weights, n, comb);
    /*
    for (std::vector<int>::iterator it = comb.begin(); it != comb.end(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;
    */
    int total = comb[comb.size() - 1];
    for (int i = total / 2; i >= 0; --i) {
        if (std::find(comb.begin(), comb.end(), i) != comb.end()) {
            int d = total - 2 * i;
            d = abs(d);
            std::cout << d << std::endl;
            break;
        }
    }
   
    delete[] weights;

    return 0;
}

