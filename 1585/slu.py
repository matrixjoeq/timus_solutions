#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1585. Penguins
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Programmer Denis has been dreaming of visiting Antarctica since his childhood.
However, there are no regular flights to Antarctica from his city. That is why
Denis has been studying the continent for the whole summer using a local cinema.
Now he knows that there are several kinds of penguins:
    Emperor Penguins, which are fond of singing;
    Little Penguins, which enjoy dancing;
    Macaroni Penguins, which like to go surfing.
Unfortunately, it was not said in the cartoons which kind of penguins was
largest in number. Petya decided to clarify this. He watched the cartoons once
more and every time he saw a penguin he jotted down its kind in his notebook.
Then he gave his notebook to you and asked you to determine the most numerous
kind of penguins.

[Input]
The first line contains the number n of entries in the notebook (1 ≤ n ≤ 1000).
In each of the next n lines, there is the name of a kind of penguins, which is
one of the following: “Emperor Penguin,” “Little Penguin,” and “Macaroni Penguin.”

[Output]
Output the most numerous kind of penguins. It is guaranteed that there is only
one such kind.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    m = { 'Emperor Penguin' : 0, 'Little Penguin' : 0, 'Macaroni Penguin' : 0 }
    for line in sys.stdin:
        if (n <= 0):
            break;
        line = line.strip('\r\n')
        m[line] = m[line] + 1
        n = n - 1

    c = 0
    r = ''
    for k, v in m.items():
        if (v > c):
            r = k
            c = v
    print r

if __name__ == '__main__':
    calc()

