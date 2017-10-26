#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1149. Sinus Dances
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Let An = sin(1–sin(2+sin(3–sin(4+…sin(n))…)
Let Sn = (…(A1+n)A2+n–1)A3+…+2)An+1
For given N print SN

[Input]
One integer N. 1 ≤ N ≤ 200

[Output]
Line containing SN
'''

import sys;
import math;

def an(n):
    a = str(n)
    for i in range(n - 1, 0, -1):
        if (i % 2):
            a = str(i) + '-' + 'sin(' + a + ')'
        else:
            a = str(i) + '+' + 'sin(' + a + ')'
    a = 'sin(' + a + ')'
    return a

def sn(n):
    s = ''
    for i in range(1, n + 1):
        r = an(i) + '+' + str(n + 1 - i)
        if (s != ''):
            s = '(' + s + ')' + r
        else:
            s = r
    return s

def calc():
    n = int(sys.stdin.readline())
    print sn(n)

if __name__ == '__main__':
    calc()

