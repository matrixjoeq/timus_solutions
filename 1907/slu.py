#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1907. Coffee and Buns
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Planet Ataraxia is known for its education centers. The people who are expected
to take high social positions in future are brought up in conditions of continuous
training and supervision from the early age. Each education center is a small
town with all the necessary utilities. During the construction of a center, a
square area is chosen which is divided into equal sections each sized 100 × 100
meters. In each of these sections they build one building, which would become
residential or academic. The outer perimeter of the center is fenced.
After a successful military operation in the Andromeda nebula the active colonization
of habitable planets has started. The need for people able to take command and lead
people to the new worlds has increased. Therefore, two new education centers should
be built on Ataraxia. Discussion about the details of the project in the local
administration is already underway for many days. During this time it was decided
that the first center will consist of a2 sections and that the second one will
consist of no more than n2 sections. The situation is complicated because, according
to requirements of the antimonopoly legislation, construction works must be performed
by at least two different companies, each of them must build an equal number of
buildings and an equal number of 100-meters segments of the fence.
You are responsible for resupplying the administration office. You understand that
while they are discussing the pros and cons of each possible size of the second
center a lot of buns and coffee will be consumed, and it's time to buy them. So
you'd like to know how many different sizes of the second center will meet the
requirements of antimonopoly legislation and, therefore, will be fully considered
by the administration.

[Input]
The only line contains integers a and n (1 ≤ a ≤ 1012; 1 ≤ n ≤ 1018).

[Output]
Output an amount of different sizes of the second center meeting the requirements
of antimonopoly legislation.
'''

import sys;
import math;

def get_min_common(x, y):
    base = int(math.sqrt(min(x, y)))
    for i in range(2, base + 1):
        if (x % i == 0 and y % i == 0):
            return i

def is_even(n):
    return (n % 2 == 0)

def is_odd(n):
    return (n % 2 == 1)

def calc():
    a, n = sys.stdin.readline().split(' ')
    a = long(a)
    n = long(n)
    r = 0
    for i in range(1, n + 1):
        if ((is_even(a) and is_even(i)) or (is_odd(a) and is_odd(i))):
            r = r + 1
        elif (get_min_common(a * a + i * i, 4 * (a + i)) > 1):
            r = r + 1

    print r

if __name__ == '__main__':
    calc()

