#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1068. Sum
Time limit: 2.0 second
Memory limit: 64 MB

[Description]
Your task is to find the sum of all integer numbers lying between 1 and N
inclusive.

[Input]
The input consists of a single integer N that is not greater than 10000 by it's
absolute value.

[Output]
Write a single integer number that is the sum of all integer numbers lying
between 1 and N inclusive.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    s = 0
    if (n < 1):
        for i in range(n, 2):
            s = s + i
    elif (n == 1):
        s = 1
    else:
        for i in range(1, n + 1):
            s = s + i
    print s

if __name__ == '__main__':
    calc()

