#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1493. One Step from Happiness
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Vova bought a ticket in a tram of the 13th route and counted the sums of the
first three and the last three digits of the ticket's number (the number has
six digits). It turned out that the sums differed by one exactly. "I'm one
step from happiness," Vova thought, "either the previous or the next ticket
is lucky." Is he right?

[Input]
The input contains the number of the ticket. The number consists of six digits,
some of which can be zeros. It is guaranteed that Vova counted correctly, i.e.,
that the sum of the first three digits differs from the sum of the last three
digits by one exactly.

[Output]
Output "Yes" if Vova is right and "No" otherwise.
'''

import sys;
import math;

def is_lucky(n):
    last_digit = n % 10
    second_last_digit = (n / 10) % 10
    third_last_digit = (n / 100) % 10
    sum_last_three = last_digit + second_last_digit + third_last_digit

    third_digit = (n / 1000) % 10
    second_digit = (n / 10000) % 10
    first_digit = (n / 100000) % 10
    sum_first_three = first_digit + second_digit + third_digit

    return (sum_first_three == sum_last_three)

def calc():
    number = int(sys.stdin.readline().strip('\r\n'))
    p = number - 1
    n = number + 1
    if (is_lucky(p) or is_lucky(n)):
        print 'Yes'
    else:
        print 'No'

if __name__ == '__main__':
    calc()

