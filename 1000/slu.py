#!/usr/bin/python

import sys

for line in sys.stdin:
    a, b = line.split(' ')
    a = int(a)
    b = int(b)
    print '{0}'.format(a + b)

