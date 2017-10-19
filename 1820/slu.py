#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1820. Ural Steaks
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
After the personal contest, happy but hungry programmers dropped into the
restaurant “Ural Steaks” and ordered n specialty steaks. Each steak is
cooked by frying each of its sides on a frying pan for one minute.
Unfortunately, the chef has only one frying pan, on which at most k steaks
can be cooked simultaneously. Find the time the chef needs to cook the steaks.

[Input]
The only input line contains the integers n and k separated with a space (1 ≤ n,
k ≤ 1000).

[Output]
Output the minimal number of minutes in which the chef can cook n steaks.
'''

import sys;
import math;

def calc():
    line = sys.stdin.readline().strip('\r\n')
    n, k = line.split(' ')
    n = int(n)
    s = n * 2
    k = int(k)
    if (n <= k):
        print 2
    else:
        t = int(s / k)
        if (s % k):
            t = t + 1
        print t

if __name__ == '__main__':
    calc()

