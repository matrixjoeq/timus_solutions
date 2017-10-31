#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1881. Long problem statement
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
While Fedya was writing the statement of the problem GOV Chronicles, he realized
that there might be not enough paper to print the statements. He also discovered
that his text editor didn't have the feature of calculating the number of pages
in a text. Then Fedya decided to write a program that would calculate the number
of pages for any given text.
Fedya knew that there were h lines on each page and w symbols in each line. Any
two neighboring words in a line were separated by exactly one space. If there was
no place for a word in a line, Fedya didn't hyphen it but put the whole word at
the beginning of the next line.

[Input]
The first line contains the integers h, w, and n, which are the number of lines
on a page, the number of symbols in a line, and the number of words in the
problem statement, respectively (1 ≤ h, w ≤ 100; 1 ≤ n ≤ 10 000). The statement
written by Fedya is given in the following n lines, one word per line. The words
are nonempty and consist of uppercase and lowercase English letters and
punctuation marks (period, comma, exclamation mark, and question mark); the
length of each word is at most w. The total length of all the words is at most
10000.

[Output]
Output the number of pages in the problem statement.
'''

import sys;
import math;

def calc():
    h, w, n = sys.stdin.readline().strip('\r\n').split(' ')
    h = int(h)
    w = int(w)
    n = int(n)
    line = 0
    index = 0
    while (n > 0):
        n = n - 1
        word = sys.stdin.readline().strip('\r\n')
        if (index == 0):
            line = line + 1

        if (index + len(word) > w):
            line = line + 1
            index = len(word)
        else:
            index = index + len(word)

        if (index == w or (index + 1) == w):
            index = 0
        else:
            index = index + 1

    p = int(line / h)
    if (line % h > 0):
        p = p + 1
    print p


if __name__ == '__main__':
    calc()

