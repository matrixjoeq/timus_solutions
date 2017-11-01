#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1014. Product of Digits
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Your task is to find the minimal positive integer number Q so that the product
of digits of Q is exactly equal to N.

[Input]
The input contains the single integer number N (0 ≤ N ≤ 10^9).

[Output]
Your program should print to the output the only number Q. If such a number
does not exist print −1.
'''

import sys;
import math;

def get_factors(n):
    f = {}
    i = 9
    while (i > 1):
        if (n % i == 0):
            f[i] = 0
            while (n % i == 0):
                f[i] = f[i] + 1
                n = n / i
        i = i - 1

    if (n != 1):
        f[n] = 1

    return f

def get_result(n):
    if (n == 0):
        return 10
    elif (n >= 1 and n <= 9):
        return n
    else:
        f = get_factors(n)
        #print f
        r = ''
        keys = f.keys()
        keys.sort()
        for k in keys:
            if (k > 9):
                return -1
            r = r + str(k) * f[k]
        return int(r)

def calc():
    n = int(sys.stdin.readline().strip('\r\n'))
    r = get_result(n)
    #print '{0} : {1}'.format(n, r)
    print r

if __name__ == '__main__':
    calc()

