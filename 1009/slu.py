#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1009. K-based Numbers
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
Let’s consider K-based numbers, containing exactly N digits. We define a number
to be valid if its K-based notation doesn’t contain two successive zeros. For
example:
    1010230 is a valid 7-digit number;
    1000198 is not a valid number;
    0001235 is not a 7-digit number, it is a 4-digit number.
Given two numbers N and K, you are to calculate an amount of valid K based
numbers, containing N digits.
You may assume that 2 ≤ K ≤ 10; N ≥ 2; N + K ≤ 18.

[Input]
The numbers N and K in decimal notation separated by the line break.

[Output]
The result in decimal notation.
'''

import sys
import math

def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def f(n, k):
    if n == 1:
        return k - 1
    return (f(n - 1, k) * (k - 1) + int(math.pow(k - 1, n - 1)))


def calc():
    n = get_int_from_stdin()
    k = get_int_from_stdin()
    print f(n, k)


if __name__ == '__main__':
    calc()
