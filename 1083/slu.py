#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1083. Factorials!!!
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Definition 1. n!!…! = n(n−k)(n−2k)…(n mod k), if k doesn’t divide n; n!!…! =
n(n−k)(n−2k)…k, if k divides n (There are k marks ! in the both cases).

Definition 2. X mod Y — a remainder after division of X by Y.

For example, 10 mod 3 = 1; 3! = 3·2·1; 10!!! = 10·7·4·1.
Given numbers n and k we have calculated a value of the expression in the
first definition. Can you do it as well?

[Input]
contains the only line: one integer n, 1 ≤ n ≤ 10, then exactly one space, then
k exclamation marks, 1 ≤ k ≤ 20.

[Output]
contains one number — n!!…! (there are k marks ! here).
'''

import sys;
import math;

def calc():
    n, k = sys.stdin.readline().strip('\r\n').split(' ')
    n = int(n)
    k = len(k)
    r = n
    p = 1
    if (n > k):
        if (n % k):
            while ((n - p * k) > (n % k)):
                r = r * (n - p * k)
                p = p + 1
            r = r * (n % k)
        else:
            while ((n - p * k) > k):
                r = r * (n - p * k)
                p = p + 1
            r = r * k
    else:
        if (n % k):
            r = r % k
    print r


if __name__ == '__main__':
    calc()

