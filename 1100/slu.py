#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1100. Final Standings
Time limit: 1.0 second
Memory limit: 16 MB

[Description]
Old contest software uses bubble sort for generating final standings. But now,
there are too many teams and that software works too slow. You are asked to
write a program, which generates exactly the same final standings as old
software, but fast.

[Input]
The first line of input contains only integer 1 < N ≤ 150000 — number of teams.
Each of the next N lines contains two integers 1 ≤ ID ≤ 107 and 0 ≤ M ≤ 100.
ID — unique number of team, M — number of solved problems.

[Output]
Output should contain N lines with two integers ID and M on each. Lines should
be sorted by M in descending order as produced by bubble sort (see below).

[Notes]
Bubble sort works following way:
    while (exists A[i] and A[i+1] such as A[i] < A[i+1]) do
       Swap(A[i], A[i+1]);
'''

import sys;
import math;

def compare(x, y):
    if (x[1] > y[1]):
        return 1
    elif (x[1] < y[1]):
        return -1
    else:
        return 0

def calc():
    n = int(sys.stdin.readline())
    groups = []
    while (n > 0):
        n = n - 1
        i, s = sys.stdin.readline().strip('\r\n').split(' ')
        i = int(i)
        s = int(s)
        groups.append([i, s])
    groups.sort(cmp = compare, reverse = True)
    for i in groups:
        print '{0} {1}'.format(i[0], i[1])

if __name__ == '__main__':
    calc()

