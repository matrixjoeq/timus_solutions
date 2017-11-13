#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1638. Bookworm
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Petya bought a 100-volume edition of Advice of Veterans of Programming Contests
and hoped that the succession of his failures would come to an end. He mounted
a bookshelf on the wall and put the volumes onto the shelf in increasing order
from left to right closely to each other. But Petya didn't know that inside the
first sheet of one of the volumes there lived a mathematical worm, which was
infinitely small and very voracious. The worm started to gnaw its way through
the volumes perpendicularly to the sheets. It stopped upon reaching the last
sheet of another volume. The following day Petya discovered the damage and
became interested in how many millimeters the worm had gnawed.

[Input]
The first line contains 4 positive integers not exceeding 100 and separated by
a space: the thickness of each volume (without the covers taken into account),
the thickness of each book-cover, the number of the volume from which the worm
started its route, and the number of the volume where it stopped.

[Output]
Output the length of the worm's route.
'''

import sys
import math


def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def calc():
    w, c, s, e = get_str_from_stdin().split(' ')
    w = int(w)
    c = int(c)
    s = int(s)
    e = int(e)
    if s > e:
        print (s - e + 1) * (w + 2 * c) - 2 * c
    elif e > s:
        print (e - s - 1) * (w + 2 * c) + 2 * c
    else:
        print w


if __name__ == '__main__':
    calc()
