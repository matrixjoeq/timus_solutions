#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1224. Spiral
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
A brand new sapper robot is able to neutralize mines in a rectangular region having
integer height and width (N and M respectively). Before the robot begins its work it
is placed near the top leftmost cell of the rectangle heading right. Then the robot
starts moving and neutralizing mines making a clockwise spiral way (see picture).
The spiral twists towards the inside of the region, covering all the cells. The region
is considered safe when all the cells are visited and checked by the robot.
Your task is to determine the number of the turns the robot has to make during its work.

[Input]
The input contains two integers in the following order: N, M (1 ≤ N, M ≤ 2^31 − 1).

[Output]
The output consists of a single integer value — the number of the turns.
'''

import sys
import math

def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def t(n, m):
    if n == 1:
        return 0

    if m == 1:
        # here n must be larger than 1
        return 1

    if n == 2:
        # here m must be larger than 1
        return 2

    if m == 2:
        # here n must be larger than 2
        return 3

    if m >= n:
        if n % 2 == 0:
            p = n / 2 - 1
            return t(2, m - 2 * p) + 4 * p
        else:
            p = (n - 1) / 2
            return t(1, m - 2 * p) + 4 * p
    else:
        if m % 2 == 0:
            p = m / 2 - 1
            return t(n - 2 * p, 2) + 4 * p
        else:
            p = (m - 1) / 2
            return t(n - 2 * p, 1) + 4 * p


def calc():
    n, m = get_str_from_stdin().split(' ')
    n = int(n)
    m = int(m)
    print t(n, m)


if __name__ == '__main__':
    calc()
