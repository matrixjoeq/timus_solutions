#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1044. Lucky Tickets. Easy!
Time limit: 2.0 second
Memory limit: 64 MB

[Description]
The public transport administration of Ekaterinburg is anxious about the fact
that passengers don’t like to pay for passage doing their best to avoid the
fee. All the measures that had been taken (hard currency premiums for all of
the chiefs, increase in conductors’ salaries, reduction of number of buses)
were in vain. An advisor especially invited from the Ural State University
says that personally he doesn’t buy tickets because he rarely comes across the
lucky ones (a ticket is lucky if the sum of the first three digits in its
number equals to the sum of the last three ones). So, the way out is found — of
course, tickets must be numbered in sequence, but the number of digits on a
ticket may be changed. Say, if there were only two digits, there would have
been ten lucky tickets (with numbers 00, 11, …, 99). Maybe under the
circumstances the ratio of the lucky tickets to the common ones is greater?
And what if we take four digits? A huge work has brought the long-awaited
result: in this case there will be 670 lucky tickets. But what to do if there
are six or more digits?

So you are to save public transport of our city. Write a program that determines
a number of lucky tickets for the given number of digits. By the way, there
can’t be more than nine digits on one ticket.

[Input]
contains a positive even integer not greater than 9.

[Output]
should contain a number of tickets such that the sum of the first half of
digits is equal to the sum of the second half of digits.
'''

import sys
import math


def calc():
    n = int(sys.stdin.readline())
    n = n / 2
    max_n = int(math.pow(10, n))
    sum_d = {}
    digits = []
    for i in range(n):
        digits.append(0)

    for i in range(max_n):
        for j in range(n):
            digits[j] = i % 10
            i = i / 10
        s = sum(digits)
        if s in sum_d.keys():
            sum_d[s] = sum_d[s] + 1
        else:
            sum_d[s] = 1
    r = 0
    for v in sum_d.values():
        r = r + v * v

    print r


if __name__ == '__main__':
    calc()
