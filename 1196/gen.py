#!/usr/bin/python
# -*- coding: utf-8 -*-

import random
import math

def gen():
    random.seed()
    r = []
    limit = int(math.pow(10, 9))
    n = int(math.pow(10, 6))
    for i in range(15000):
        r.append(random.randrange(1, limit))
    r.sort()

    s = []
    for i in range(n):
        s.append(random.randrange(1, limit))

    with open(r'./test.txt', r'wb') as f:
        f.write('15000\r\n')
        for i in r:
            f.write(str(i) + '\r\n')
        f.write(str(n) + '\r\n')
        for i in s:
            f.write(str(i) + '\r\n')

if (__name__ == '__main__'):
    gen()

