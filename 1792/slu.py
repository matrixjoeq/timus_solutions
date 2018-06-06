#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1792. Hamming Code
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Let us consider four disks intersecting as in the figure. Each of the three shapes formed by the intersection of three
disks will be called a petal.
Write zero or one on each of the disks. Then write on each petal the remainder in the division by two of the sum of 
integers on the disks that contain this petal. For example, if there were the integers 0, 1, 0, and 1 written on the 
disks, then the integers written on the petals will be 0, 1, and 0 (the disks and petals are given in the order shown 
in the figure).
This scheme is called a Hamming code. It has an interesting property: if you enemy changes secretely any of the seven 
integers, you can determine uniquely which integer has been changed. Solve this problem and you will know how this can 
be done.

[Input]
The only line contains seven integers separated with a space, each of them being zero or one. The first four integers
are those written on the disks in the order shown in the figure. The following three integers are those written on the 
petals in the order shown in the figure

[Output]
Output one line containing seven integers separated with a space. The integers must form a Hamming code. The set of 
integers may differ from the input set by one integer at most. It is guaranteed that either the input set is a Hamming 
code or a Hamming code can be obtained from it by changing exactly one integer.
'''

import sys
import math
import copy

def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    return int(get_str_from_stdin())


def convert_to_int_list(l):
    _l = []
    for i in l:
        _l.append(int(i))
    return _l
    
    
def is_hamming_code(code):
    disks = code[:4]
    petals = code[4:]
    p1 = (disks[1] + disks[2] + disks[3]) % 2
    p2 = (disks[0] + disks[2] + disks[3]) % 2
    p3 = (disks[0] + disks[1] + disks[3]) % 2
    p = [p1, p2, p3]
    return p == petals

    
def get_hamming_code(code):    
    if (is_hamming_code(code)):
        return code
    
    for i in range(4):
        _code = copy.deepcopy(code)
        _code[i] = (_code[i] + 1) % 2
        if is_hamming_code(_code):
            return _code
        
    return None
    
    
def calc():
    line = get_str_from_stdin()
    code = line.split(' ')
    code = convert_to_int_list(code)
    code = get_hamming_code(code)
    
    result = ''
    i = 1
    for c in code:
        result = result + str(c)
        if (i < len(code)):
            result = result + ' '
        i = i + 1
    sys.stdout.write(result)


if __name__ == '__main__':
    calc()
