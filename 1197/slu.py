#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1197. Lonesome Knight
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
The statement of this problem is very simple: you are to determine how many
squares of the chessboard can be attacked by a knight standing alone on the
board. Recall that a knight moves two squares forward (horizontally or
vertically in any direction) and then one square sideways (perpedicularly
to the first direction).

[Input]
The first line contains the number N of test cases, 1 ≤ N ≤ 100. Each of
the following N lines contains a test: two characters. The first character
is a lowercase English letter from 'a' to 'h' and the second character is an
integer from 1 to 8; they specify the rank and file of the square at which the
knight is standing.

[Output]
Output N lines. Each line should contain the number of the squares of the
chessboard that are under attack by the knight.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    while (n > 0):
        line = sys.stdin.readline()
        r = line[0]
        f = line[1]
        if ((r == 'a' or r == 'h') and (f == '1' or f == '8')):
            print 2
        elif (((r == 'a' or r == 'h') and (f == '2' or f == '7')) or
              ((r == 'b' or r == 'g') and (f == '1' or f == '8'))):
            print 3
        elif (((r == 'a' or r == 'h') and (f >= '3' and f <= '6')) or
              ((r >= 'c' and r <= 'f') and (f == '1' or f == '8'))):
            print 4
        elif ((r == 'b' or r == 'g') and (f == '2' or f == '7')):
            print 4
        elif (((r == 'b' or r == 'g') and (f >= '3' and f <= '6')) or
              ((r >= 'c' and r <= 'f') and (f == '2' or f == '7'))):
            print 6
        else:
            print 8
        n = n - 1

if __name__ == '__main__':
    calc()

