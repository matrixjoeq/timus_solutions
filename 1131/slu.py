#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1131. Copying
Time limit: 0.25 second
Memory limit: 64 MB

[Description]
A new educating program was received by the kindergarten. Of course, children
have discovered it immediately and want to play with it as soon as possible.
In order to let them do it the program has to be copied to all the N computers
that the kindergarten had bought just before the default of 1998. At the moment
the program is installed only on one computer. Other computers do not have
floppy drives and are not connected with a local network. The only way to
transfer information from one computer to another is to copy it using a
null-modem cable (a cable that connects two computers directly). So, if the
program is installed on a computer, it can be copied to some other (but only
one!) computer within an hour. There are only K null-modem cables in the
kindergarten. Your task is to estimate the minimal time necessary for copying
the program to all the computers in the kindergarten.

[Input]
The only input line contains two integers separated with a space: N and K
(1 ≤ N ≤ 10^9; 1 ≤ K ≤ 10^9).

[Output]
You are to output the minimal time (in hours) necessary for copying of the
program to all the computers.
'''

import sys;
import math;

def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')

def get_int_from_stdin():
    return int(get_str_from_stdin())

def calc():
    n, k = sys.stdin.readline().strip('\r\n').split(' ')
    n = int(n)
    k = int(k)
    r = 0

    m = int(math.log(k, 2))
    n_m = int(math.pow(2, m + 1))
    if (n >= n_m):
        r = m + 1
        y = n - n_m
        r = r + int(y / k)
        if (y % k > 0):
            r = r + 1
    else:
        y = math.log(n, 2)
        r = int(y)
        if (r < y):
            r = r + 1
    print r

if __name__ == '__main__':
    calc()

