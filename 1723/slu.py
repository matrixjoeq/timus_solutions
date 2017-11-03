#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1723. Sandro's Book
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
It's been quite a number of years since Lich Sandro retired. Sometimes in the
evenings, when he feels especially lonely, he takes a book that was presented
to him by his student magicians on the occasion of his retirement.
This evening the great magician is also reading the book. One of the chapters
describes Sandro's famous discovery: he invented a universal spell many years
ago. Any substring (a few consecutive symbols of the string) of the universal
spell is also a spell, and its power is equal to the number of times this spell
is encountered in the universal spell (for example, the string “ue” encounters
in the string “queue” twice, and the string “aba” encounters in the string
“abababa” three times).
Sandro has a lot of free time now and he wants to find the most powerful spell.
Help Sandro do it.

[Input]
The only input line contains the universal spell invented by Sandro. The spell
is a non-empty string consisting of lowercase English letters with length at
most 50.

[Output]
Output any of the most powerful spells, according to Sandro's definition.
'''

import sys;
import math;
#import pprint;
#pp = pprint.PrettyPrinter(indent = 4)

def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')

def get_int_from_stdin():
    return int(get_str_from_stdin())

def calc():
    spell = get_str_from_stdin()

    # Note:
    # Actually, one letter is also a 'substring'.
    # The definition of 'substring' in description is not accurate.
    # So 'substring' window size starts from 1.
    sub = {}
    for w in range(1, len(spell) + 1):
        for i in range(len(spell) + 1 - w):
            s = spell[i:i + w]
            if (sub.has_key(s)):
                sub[s] = sub[s] + 1
            else:
                sub[s] = 1
    key = None
    value = 0
    #pp.pprint(sub)
    for k, v in sub.items():
        if (v > value):
            key = k
            value = v
    print key

if __name__ == '__main__':
    calc()

