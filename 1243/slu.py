#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1243. Divorce of the Seven Dwarfs
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
After the Snow White with her bridegroom had left the house of the seven dwarfs,
their peaceful and prosperous life has come to an end. Each dwarf blames others
to be the reason of the Snow White's leave. To stop everlasting quarrels, the
dwarfs decided to part. According to an ancient law, their common possessions
should be divided in the most fair way, which means that all the dwarfs should
get equal parts. Everything that the dwarfs cannot divide in a fair way they
give to the Snow White. For example, after dividing 26 old boots, each dwarf got
3 old boots, and the Snow White got the remaining 5 old boots. Some of the
numbers are very large, for example, the dwarfs have 123456123456 poppy seeds,
so it is not easy to calculate that the Snow White gets only one seed. To speed
up the divorce, help the dwarfs to determine quickly the Snow White's part.

[Input]
The only line contains an integer N that represents the number of similar items
that the dwarfs want to divide (1 ≤ N ≤ 10^50).

[Output]
You should output the number of items that pass into the possession of the Snow
White.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    print (n % 7)

if __name__ == '__main__':
    calc()

