#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1567. SMS-spam
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Petr, a student, decided to start his own business. He offers SMS advertising
services to the business owners renting offices in the newly built “Prisma”
tower. If an office owner wants to use the service, he devises a slogan and
Petr texts it from his personal phone to thousands of Ekaterinburg citizens
(he already bought the pirated list of mobile phone numbers). The cost of
each slogan sent is a sum of costs of each character typed. Cost of an
individual character is determined according to a very simple scheme: each
tap at the phone's keyboard costs 1 rouble.
Petr's phone doesn't support sophisticated text input technologies, such as
T9, and only the english alphabet can be used.

The “_” character in the table denotes whitespace. If you want to, for
example, type “a”, you need to press the “1” button once. To type “k”, you
press “4” twice. To type “!”, press “0” three times.
Petr has to apply this simple algorithm to calculate the cost of every slogan
he sends. However, Petr is a very busy man (and, as a matter of fact, doesn't
bother to learn arithmetics, because he's a Philosophy student). You just have
to help Petr, you are his best friend after all.

[Input]
The single line of input contains the slogan. Slogan consists of words, spaces,
commas, full stops and exclamation marks. All the words consist of lowercase
english letters. Slogan can't be longer than 1000 characters.

[Output]
Output a single number representing the cost of the given slogan, according to
Petr's pricing.
'''

import sys;
import math;

cost_table = {
    'a' : 1, 'b' : 2, 'c' : 3,
    'd' : 1, 'e' : 2, 'f' : 3,
    'g' : 1, 'h' : 2, 'i' : 3,
    'j' : 1, 'k' : 2, 'l' : 3,
    'm' : 1, 'n' : 2, 'o' : 3,
    'p' : 1, 'q' : 2, 'r' : 3,
    's' : 1, 't' : 2, 'u' : 3,
    'v' : 1, 'w' : 2, 'x' : 3,
    'y' : 1, 'z' : 2,
    '.' : 1, ',' : 2, '!' : 3,
    ' ' : 1}

def calc():
    line = sys.stdin.readline().strip('\r\n')
    cost = 0
    for c in line:
        cost = cost + cost_table[c]

    print cost

if __name__ == '__main__':
    calc()

