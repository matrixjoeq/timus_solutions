#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
[Description]
Old Captain Jack Sparrow’s friend Tia Dalma, the fortuneteller and prophetess, often makes potions. She has an 
outstanding collection of the rarest ingredients such as rat tails, fingers of drowned, tears of virgins and so on. 
And all these ingredients require special care.
Recently Tia Dalma received some good skins of bats as a payment, and now she wants to dry them. To dry ingredients
fortuneteller usually uses specially prepared books as the magical properties of the skins could be lost during 
prolonged contact with other objects. Tia Dalma knows how many sheets should be on both sides of the skin to save it
unspoiled. For a i-th skin that number is ai, that is, the distance from it to the neighboring skins and the book cover
can’t be less than ai sheets. Help a fortuneteller determine the minimum number of sheets that should be in the book to
save rare ingredients from damage.

[Input]
The first line contains integer n that is the number of skins (1 ≤ n ≤ 100). 
The second line contains n integers ai (1 ≤ ai ≤ 100).

[Output]
Output the minimal required number of sheets in the book.

'''

import sys
import math


def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def compare(x, y):
    _x = int(x)
    _y = int(y)
    if (_x < _y):
        return -1
    elif (_x == _y):
        return 0
    else:
        return 1

def calc():
    n = get_int_from_stdin()
    line = get_str_from_stdin()
    ai = line.split(' ')
    ai.sort(cmp = compare)
    sheets = 0
    for i in ai:
        sheets = sheets + int(i)
    sheets = sheets + int(ai[len(ai) - 1])
    
    sys.stdout.write(str(sheets))


if __name__ == '__main__':
    calc()
