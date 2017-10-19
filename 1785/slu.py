#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1785. Lost in Localization
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
The Lavin Interactive Company, which has developed the turn-based strategy
Losers-V, is constantly extending its target market by localizing the game
to as many languages as it can. In particular, they are interested in
creating a version of the game in Anindilyakwa, which is one of the languages
spoken by indigenous Australians.
However, the localization is complicated by the fact that Anindilyakwa has
no numerals. How can a phrase such as “You have seven black dragons and your
enemy has forty black dragons” be translated into this language? The localizers
have decided to translate it as follows: “You have few black dragons and your
enemy has lots of black dragons.” They have compiled a table showing the rule
of replacing numbers of monsters by Anindilyakwa words.
NumberDesignation in Anindilyakwa
    from 1 to 4      few
    from 5 to 9      several
    from 10 to 19    pack
    from 20 to 49    lots
    from 50 to 99    horde
    from 100 to 249  throng
    from 250 to 499  swarm
    from 500 to 999  zounds
    from 1000        legion
Help the localizers automatize the process. Write a program that would output
the appropriate word given the number of monsters.

[Input]
The only line contains the number of monsters n (1 ≤ n ≤ 2000).

[Output]
Output the word corresponding to the given number of monsters in the
Anindilyakwa language.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    if (n >= 1 and n <= 4):
        print 'few'
    elif (n >= 5 and n <= 9):
        print 'several'
    elif (n >= 10 and n <= 19):
        print 'pack'
    elif (n >= 20 and n <= 49):
        print 'lots'
    elif (n >= 50 and n <= 99):
        print 'horde'
    elif (n >= 100 and n <= 249):
        print 'throng'
    elif (n >= 250 and n <= 499):
        print 'swarm'
    elif (n >= 500 and n <= 999):
        print 'zounds'
    elif (n >= 1000):
        print 'legion'

if __name__ == '__main__':
    calc()

