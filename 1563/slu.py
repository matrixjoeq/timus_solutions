#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1563. Bayan
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
As everybody knows, there are a lot of stores in skyscrapers, it's the favourite
place of glamorous girls. Blonde Cindy loves only one thing — the shopping. Today
is one of the best days, she's going shopping to the new skyscraper “Prisma”. At
first she decided to visit all the stores. But actually the “Prisma” is so large
that you can find not just one store of each brand. Every time when Cindy found
the brand, she has visited before, she told “Bayan”, and went on shopping.
Cindy saw all the stores in the “Prisma”. So how many times did she tell “Bayan”?

[Input]
First line contains single integer N representing the number of stores in the
“Prisma” (1 ≤ N ≤ 1000). In each of next N lines the brand of store is written.
The brands are the strings of Latin letters and blanks. The length of the string
is from 1 to 30. There are no brands, that differ only in register.

[Output]
Print the number of stores, Cindy didn't visit.
'''

import sys;
import math;

def calc():
    n = int(sys.stdin.readline())
    stores = []
    not_visited = 0
    while (n > 0):
        n = n - 1
        store = sys.stdin.readline().strip('\r\n')
        if (store in stores):
            not_visited = not_visited + 1
        else:
            stores.append(store)

    print not_visited

if __name__ == '__main__':
    calc()

