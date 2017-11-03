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

import sys;
import math;

def get_int_from_stdin():
    return int(sys.stdin.readline().strip('\r\n')

def calc():
    n = get_int_from_stdin()
    weights = sys.stdin.readline().strip('\r\n').split(' ')
    for i in range(n):
        weights[i] = int(weights[i])

    weights.sort(reverse=True)
    if (n == 1):
        print weights[0]
    elif (n == 2):
        print (weights[0] - weights[1])
    elif (n == 3):
        print abs(weights[0] - weights[1] - weights[2])
    else:



if __name__ == '__main__':
    calc()
