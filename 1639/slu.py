#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1639. Chocolate 2
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Little Boy is mad at Karlsson, who ate all the sweets in the flat and even went
to the neighbours to eat their sweets too. Now Little Boy's parents brought
home a chocolate bar, and, sure enough, Karlsson is here already and wants to
eat it. However, this time Little Boy has firmly decided that not a single
piece of chocolate will go to this glutton. Little Boy wants to use Karlsson's
addiction to the games of chance and suggests playing the following game. A
chocolate bar can be considered as a rectangle of square “units” arranged in m
rows and n columns and separated by “lines”. Two players take alternate turns.
At his turn, a player must take one piece of chocolate and split it into two
along one of the lines. If a player can't make a legal move (which happens when
all pieces of chocolate consist of a single unit square), he loses, and the
winner takes all the chocolate.
But Karlsson is smart enough! He immediately understood who should make the
first turn in order for Karlsson to win, assuming that players take optimal
turns. Can you guess that?

[Input]
The only line of the input contains space-separated integers m and n
(1 ≤ m, n ≤ 50).

[Output]
If Karlsson should start the game in order to win, output “[:=[first]”;
otherwise, output “[second]=:]”.
'''

import sys;
import math;

def calc():
    line = sys.stdin.readline().strip('\r\n')
    m, n = line.split(' ')
    m = int(m)
    n = int(n)
    if ((m * n) % 2 == 0):
        print "[:=[first]"
    else:
        print "[second]=:]"

if __name__ == '__main__':
    calc()
