#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2066. Simple Expression
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
You probably know that Alex is a very serious mathematician and he likes to
solve serious problems. This is another problem from Alex.
You are given three nonnegative integers a, b, c. You have to arrange them
in some order and put +, − or × signs between them to minimize the outcome
of the resulting expression. You are not allowed to use unary minus and
parentheses in the expression. There must be exactly one sign between every
pair of neighbouring numbers. You should use standard order for performing
operations (multiplication first, addition and subtraction then).

[Input]
There are three lines with one integer in each line. The numbers are arranged
in non-decreasing order (0 ≤ a ≤ b ≤ c ≤ 100).

[Output]
Print one number — the minimal outcome.
'''

import sys;
import math;

def calc():
    a = int(sys.stdin.readline())
    b = int(sys.stdin.readline())
    c = int(sys.stdin.readline())
    if (b <= 1):
        print (a - b - c)
    else:
        print (a - b * c)

if __name__ == '__main__':
    calc()

