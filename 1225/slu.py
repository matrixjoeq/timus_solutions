#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1225. Flags
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
On the Day of the Flag of Russia a shop-owner decided to decorate the show-window
of his shop with textile stripes of white, blue and red colors. He wants to satisfy
the following conditions:
    1. Stripes of the same color cannot be placed next to each other.
    2. A blue stripe must always be placed between a white and a red or between a red
       and a white one.
Determine the number of the ways to fulfill his wish.

[Input]
N, the number of the stripes, 1 ≤ N ≤ 45.

[Output]
M, the number of the ways to decorate the shop-window.
'''

import sys;
import math;

def f(n):
    if (n == 1 or n == 2):
        return 2
    elif (n == 3):
        return 4
    return (2 * f(n - 1) - f(n - 3))

def calc():
    n = int(sys.stdin.readline())
    print f(n)

if __name__ == '__main__':
    calc()

