#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1079. Maximum
Time limit: 2.0 second
Memory limit: 64 MB

[Description]
Consider the sequence of numbers ai, i = 0, 1, 2, …, which satisfies the
following requirements:
    a0 = 0
    a1 = 1
    a2i = ai
    a2i+1 = ai + ai+1
    for every i = 1, 2, 3, … .
Write a program which for a given value of n finds the largest number among
the numbers a0, a1, …, an.

[Input]
You are given several test cases (not more than 10). Each test case is a line
containing an integer n (1 ≤ n ≤ 99 999). The last line of input contains 0.

[Output]
For every n in the input write the corresponding maximum value found.
'''

import sys;
import math;

records = {}

def an(n):
    if (records.has_key(n)):
        return records[n]

    r = 0
    if (n == 0 or n == 1):
        r = n
    else:
        if (n % 2 == 0):
            r = an(n / 2)
        else:
            i = int(n / 2)
            r = an(i) + an(i + 1)

    records[n] = r
    return r

def find_max(n):
    m = 0
    # just need to check the odd indexed values in second half
    i = int(n / 2)
    if (i % 2 == 0):
        i = i - 1
    while (i <= n):
        if (records.has_key(i)):
            if (records[i] > m):
                m = records[i]
        i = i + 2

    return m

def calc():
    while (True):
        n = int(sys.stdin.readline())
        if (n == 0):
            break
        lower_bound = int(n / 2)
        upper_bound = n
        if (lower_bound % 2 == 0):
            lower_bound = lower_bound + 1
        if (upper_bound % 2 == 0):
            upper_bound = upper_bound - 1
        # calculate an(n) n in [lower_bound, upper_bound], then we get all the values needed
        for i in range(lower_bound, upper_bound + 1, 2):
            an(i)
        #print records
        print find_max(n)

if __name__ == '__main__':
    calc()

