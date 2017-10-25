#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1209. 1, 10, 100, 1000...
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Let's consider an infinite sequence of digits constructed of ascending powers
of 10 written one after another. Here is the beginning of the sequence:
110100100010000… You are to find out what digit is located at the definite
position of the sequence.

[Input]
There is the only integer N in the first line (1 ≤ N ≤ 65535). The i-th of N
left lines contains the integer Ki — the number of position in the sequence
(1 ≤ Ki ≤ 2^31 − 1).

[Output]
You are to output N digits 0 or 1 separated with a space. More precisely, the
i-th digit of output is to be equal to the Ki-th digit of described above sequence.
'''

import sys;
import math;

def get_digit(k):
    n = int(math.sqrt(2 * (k - 1)))
    p = n * (n + 1) / 2 + 1
    if (k == p):
        return 1
    else:
        return 0

def calc():
    r = ''
    n = int(sys.stdin.readline())
    while (n > 0):
        k = int(sys.stdin.readline())
        d = get_digit(k)
        if (r != ''):
            r = r + ' '
        r = r + str(d)
        n = n - 1
    print r

if __name__ == '__main__':
    calc()

