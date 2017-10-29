#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1263. Elections
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
The next in turn elections are to come soon. All the fences are postered with
leaflets and the mail boxes are full of throwaways. Cheeky guys are looking at
us from TV’s and promise to make our life better… And programmer Vasechkin is
knee-deep in work. He is to write a program that would calculate the results
of voting.

[Input]
The first line contains a number of candidates N (1 ≤ N ≤ 10000) and a number
of electors M (1 ≤ M ≤ 10000). Then M lines follow, each one contains a number
of candidate that the elector voted for. The candidates are numbered with
integers from 1 to N.

[Output]
Output N lines. The i-th line should contain the percent of electors that voted
for the i-th candidate (to within 2 decimals).
'''

import sys;
import math;

def calc():
    n, m = sys.stdin.readline().strip('\r\n').split(' ')
    n = int(n)
    m = int(m)
    c = []
    for i in range(n):
        c.append(0)

    for i in range(m):
        v = int(sys.stdin.readline())
        c[v - 1] = c[v - 1] + 1

    for i in range(n):
        p = float(c[i] * 100) / m
        print '%.2f%s' % (p, '%')

if __name__ == '__main__':
    calc()

