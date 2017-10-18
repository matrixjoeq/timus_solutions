#!/usr/bin/python
# -*- coding: utf-8 -*- 

'''
1001. Reverse Root
Time limit: 2.0 second
Memory limit: 64 MB

[Description]
The problem is so easy, that the authors were lazy to write a statement for it!

[Input]
The input stream contains a set of integer numbers Ai (0 ≤ Ai ≤ 10^18).
The numbers are separated by any number of spaces and line breaks.
A size of the input stream does not exceed 256 KB.

[Output]
For each number Ai from the last one till the first one you should output its square root.
Each square root should be printed in a separate line with at least four digits after
decimal point.
'''

import sys;
import math;

def get_inputs():
    inputs = []
    for line in sys.stdin:
        line = line.strip('\r\n')
        l = line.split(' ')
        for i in l:
            if (i.isdigit()):
                inputs.append(i)

    return inputs

def reverse_root(inputs):
    inputs.reverse();
    for i in inputs:
        i_ = long(i)
        r = math.sqrt(i_)
        print '%.4f' % r

if __name__ == '__main__':
    reverse_root(get_inputs())
