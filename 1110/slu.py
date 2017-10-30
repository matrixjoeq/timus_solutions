#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1110. Power
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
You are given the whole numbers N, M and Y. Write a program that will find all
whole numbers X in the interval [0, M − 1] such that X^N mod M = Y.

[Input]
The input contains a single line with N, M and Y (0 < N < 999, 1 < M < 999,
0 < Y < 999) separated with one space.

[Output]
Output all numbers X separated with space on one line. The numbers must be
written in ascending order. If no such numbers exist then output −1.
'''

import sys;
import math;

def calc():
    n, m, y = sys.stdin.readline().strip('\r\n').split(' ')
    n = int(n)
    m = int(m)
    y = int(y)
    if (y >= m):
        print '-1'
        return
    '''
    (ab)%m = ((a%m)(b%m))%m
    '''
    r = []
    if (y == 1):
        r.append(1)

    for i in range(2, m):
        b = i
        p = n
        ans = 1
        while (p):
            if (p % 2):
                ans = (ans * b) % m
            b = (b * b) % m
            p = p / 2
        if (ans == y):
            r.append(i)

    if (len(r)):
        s = ''
        for i in r:
            s = s + str(i) + ' '
        s = s[:-1]
        print s
    else:
        print '-1'

if __name__ == '__main__':
    calc()

