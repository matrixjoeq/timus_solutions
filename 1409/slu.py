#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1409. Two Gangsters
Time limit: 1.0 second
Memory limit: 64 MB

[Description]

Two gangsters Harry and Larry had a rest at countryside. They decided to spend
some time shooting, so they put several beer cans (no more than 10) on a log.
Harry started to shoot cans one after another from the leftmost to the right
and Larry – from the rightmost to the left. At some moment it happened so that
they shot one and the same can.
Harry got indignant and claimed that Larry owed him a considerable sum of money
because Larry deprived him of shooting some more cans. Larry became furious
and told Harry that he owed even greater sum of money to Larry because of the
same reason. They started to argufy but nobody remembered how many cans there
were at the very beginning. And no one of them was going to search cans which
was shot. Anyway, each of them remembered exactly how many cans he shot.
Determine how many cans were not shot by Harry and how many cans were not shot
by Larry.

[Input]

The only input line contains two integers — the number of cans shot by Harry
and by Larry respectively.

[Output]

two integers — the number of cans that were not shot by Harry and the number
of cans that were not shot by Larry, respectively.
'''

import sys;
import math;

def calc():
    line = sys.stdin.readline()
    args = line.split(' ')
    left_2_right = int(args[0])
    right_2_left = int(args[1])
    total = left_2_right + right_2_left - 1
    print '{0} {1}'.format(total - left_2_right, total - right_2_left)

if __name__ == '__main__':
    calc()

