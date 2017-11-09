#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1349. Farm
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Here is a farm. Here is a farmer that counts how many animal live in his farm:
a camels, b sheep, c green cockroaches. Occurs that a^n + b^n = c^n. n is given.
You are to find all the rest.

[Input]
n (0 ≤ n ≤ 100)

[Output]
Three different integers (a, b and c) such that a^n + b^n = c^n,
1 ≤ a, b, c ≤ 100.
If there are several solutions you should output the one where a is minimal.
If there are several solutions with the minimal a you should output the one with
minimal b, and so on. Output −1 if there is no solution.
'''

import sys
import math


def calc():
    n = int(sys.stdin.readline())
    if (n == 0):
        print '-1'
        return
    # for specific n, we can get the range for a, since a < b < c
    # 2*(a^n) < a^n + b^n = c^n
    max_a = int(math.pow(math.pow(100, n) / 2.0, 1.0 / n))
    for a in range(1, max_a + 1):
        for b in range(a + 1, 100):
            c_n = math.pow(a, n) + math.pow(b, n)
            c = math.pow(c_n, 1.0 / n)
            if math.modf(c)[0] == 0.0 and c > b:
                print '{0} {1} {2}'.format(a, b, int(c))
                return
    print '-1'


if __name__ == '__main__':
    calc()
