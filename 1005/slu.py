#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1005. Stone Pile
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
You have a number of stones with known weights w1, …, wn. Write a program that
will rearrange the stones into two piles such that weight difference between
the piles is minimal.

[Input]
Input contains the number of stones n (1 ≤ n ≤ 20) and weights of the stones
w1, …, wn (integers, 1 ≤ wi ≤ 100000) delimited by white spaces.

[Output]
Your program should output a number representing the minimal possible weight
difference between stone piles.
'''

import sys
import math


def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def get_combinations(pile):
    n = len(pile)
    comb = []
    for mask in range(1, 1 << n + 1):
        v = 0
        for i in range(n):
            if (1 << i) & mask:
                v = v + pile[i]
        if v not in comb:
            comb.append(v)
    comb.sort()

    return comb


def calc():
    n = get_int_from_stdin()
    weights = sys.stdin.readline().strip('\r\n').split(' ')
    for i in range(n):
        weights[i] = int(weights[i])

    comb = get_combinations(weights)
    #print comb
    total = sum(weights)
    for i in range(int(total / 2), -1, -1):
        if i in comb:
            j = total - i
            d = abs(i - j)
            print d
            return


if __name__ == '__main__':
    calc()
