#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1196. History Exam
Time limit: 1.5 second
Memory limit: 64 MB

[Description]
Professor of history decided to simplify the examination process. At the exam,
every student should write a list of historic dates she knows (she should write
the years only and, of course, must be able to explain what event took place
in this or that year). Professor has a list of dates that students must know.
In order to decide upon the student's mark, Professor counts the number of dates
in the student's list that are also present in his list. The student gets her
mark according to the number of coincidences.
Your task is to automatize this process. Write a program that would count the
number of dates in the student's list that also occur in Professor's list.

[Input]
The first line contains the number N of dates in Professor's list, 1 ≤ N ≤ 15000.
The following N lines contain this list, one number per line. Each date is a
positive integer not exceeding 10^9. Professor's list is sorted in non-descending
order. The following line contains the number M of dates in the student's list,
1 ≤ M ≤ 10^6. Then there is the list itself; it is unsorted. The dates here satisfy
the same restriction. Both in Professor's and in the student's lists dates can
appear more than once.

[Output]
Output the number of dates in the student's that are also contained in Professor's
list.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    p = []
    while (n > 0):
        n = n - 1
        date = int(sys.stdin.readline())
        if (len(p) == 0):
            p.append(date)
        else:
            if (date != p[-1]):
                p.append(date)

    m = int(sys.stdin.readline())
    s = {}
    while (m > 0):
        m = m - 1
        date = int(sys.stdin.readline())
        if (s.has_key(date)):
            s[date] = s[date] + 1
        else:
            s[date] = 1

    r = 0
    if (len(p) <= len(s)):
        for i in p:
            if (s.has_key(i)):
                r = r + s[i]
    else:
        for k, v in s.items():
            if (k in p):
                r = r + v
    print r

if __name__ == '__main__':
    calc()

