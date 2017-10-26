#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2056. Scholarship
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
At last the first term at the University came to its finish. Android Vasya has
already passed all the exams and wants to know if he gets a scholarship. There
is the following practice of giving scholarship to students at the University:
    if a student has got satisfactory marks, the scholarship is not given,
    if a student has passed through the examination period with only excellent
    marks, he gets a personal scholarship,
    if a student doesn’t get a personal scholarship and his average mark is not
    less than 4.5, he gets a high scholarship,
    if a student gets neither high nor personal scholarship and doesn’t have
    satisfactory marks, he gets a common scholarship.
A satisfactory mark corresponds to value 3, a good mark corresponds to value 4,
and an excellent mark corresponds to value 5. An average mark for a student is
the average value of all the marks this student got in his exams. Help Vasya
find out which scholarship he gets.

[Input]
The first line contains an integer n that is the number of exams (1 ≤ n ≤ 10).
In the i-th of the next n lines there is an integer mi that is value of Vasya’s
mark in i-th exam (3 ≤ mi ≤ 5).

[Output]
If Vasya doesn’t get any scholarship output “None”. If he gets a common scholar-
ship output “Common”, if he gets a high scholarship output “High”, if he gets a
personal one output “Named”.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    scholarship = 'None'
    satisfactory = False
    personal = True
    total = 0
    for i in range(n):
        score = int(sys.stdin.readline())
        if (score != 5):
            personal = False
        if (score <= 3):
            satisfactory = True
        total = total + score

    if (not satisfactory):
        if (personal):
            scholarship = 'Named'
        else:
            average = float(total) / n
            if (average >= 4.5):
                scholarship = 'High'
            else:
                scholarship = 'Common'

    print scholarship

if __name__ == '__main__':
    calc()

