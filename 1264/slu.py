#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1264. Workdays
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
After a success of the previous Vasechkin’s program that allowed to calculate
the results of the elections in cause of two days Artemy Sidorovich was placed
at the head of the department. At the moment Artemy Sidorovich prepares a task
for his subordinate — programmer Petechkin. The task is to write a very useful
function that would ease the life of all the department programmers. For each
integer from 0 to M the function would calculate how many times this number
appears in the N-element array. Artemy Sidorovich deems that the function
should work as follows (the sample code for N = 3, M = 1):
if (arr[0]==0) ++count[0];
if (arr[0]==1) ++count[1];
if (arr[1]==0) ++count[0];
if (arr[1]==1) ++count[1];
if (arr[2]==0) ++count[0];
if (arr[2]==1) ++count[1];

Artemy Sidorovich wants to estimate the time that Petechkin will need to
execute the task. We know that Petechkin needs one second to write a line of
the code (he’s fast, isn’t he?). Artemy Sidorovich doesn’t know exactly bounds
for M and N. Your task is to write program that would calculate a number of
seconds that Petechkin will write the code.

[Input]
The only line contains integers N (0 ≤ N ≤ 40000) and M (0 ≤ M ≤ 40000).

[Output]
Output an amount of seconds that Petechkin needs to write the program.
'''

import sys;
import math;

def calc():
    line = sys.stdin.readline()
    n, m = line.split(' ')
    n = int(n)
    m = int(m)
    print (n * (m + 1))

if __name__ == '__main__':
    calc()

