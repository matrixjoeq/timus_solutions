#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2031. Overturned Numbers
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Little Pierre was surfing the Internet and came across an interesting puzzle:
|    |    |    |     |  c |    |
|    |    |    |     |  a |    |
| 16 | 06 | 68 |  88 |  r | 98 |
--------------------------------
What is the number under the car?
It took some time before Pierre solved the puzzle, but eventually he understood that there were overturned numbers 
86, 88, 89, 90, and 91 in the picture and the answer was the number 87.
Now Pierre wants to entertain his friends with similar puzzles. He wants to construct a sequence of n numbers such that
its overturning produces a consecutive segment of the positive integers. Pierre intends to use one-digit integers 
supplemented with a leading zero and two-digit integers only. To avoid ambiguity, note that when the digits 0, 1, and 8
are overturned, they remain the same, the digits 6 and 9 are converted into each other, and the remaining digits become
unreadable symbols.

[Input]
The only line contains the number n of integers in a sequence (1 ≤ n ≤ 99).

[Output]
If there is no sequence of length n with the above property, output “Glupenky Pierre” (“Silly Pierre” in Russian). 
Otherwise, output any of such sequences. The numbers in the sequence should be separated with a space.
'''

import sys
import math


def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def calc():
    n = get_int_from_stdin()
    if n == 1:
        sys.stdout.write('01')
    elif n == 2:
        sys.stdout.write('11 01')
    elif n == 3:
        sys.stdout.write('16 06 68')
    elif n == 4:
        sys.stdout.write('16 06 68 88')
    else:
        sys.stdout.write('Glupenky Pierre')


if __name__ == '__main__':
    calc()
