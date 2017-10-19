#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2001. Mathematicians and Berries
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
One day, two mathematicians were walking in the forest and picking berries.
They’d been walking for two hours, and then they stopped and decided to see
who’s got more berries. They took out the scales (can you imagine a
mathematician going to the forest without any scales?) and they weighed
their baskets with berries. They wrote the resulting numbers a1 and b1 down
on a piece of paper. Then the second mathematician put all his berries to
the first one’s basket (so that his basket became completely empty) and they
weighed their baskets again and they received numbers a2 and b2, correspondingly.
At last, the first mathematician put all the berries to the second one’s basket
(so that his basket became completely empty); they weighed the baskets and got
numbers a3 and b3, correspondingly. This data was enough to find the winner
and the happy mathematicians moved on. Your task is to calculate the mass of
the berries in each mathematician’s basket by the start of the competition.

[Input]
The input data consists of three lines. The i’th line (1 ≤ i ≤ 3) contains
integers ai and bi (0 ≤ ai, bi ≤ 10 000).

[Output]
Output the weight of berries in the basket of the first and the second
mathematician correspondingly.
'''

import sys;
import math;

def calc():
    lines = []
    for line in sys.stdin:
        lines.append(line)

    init_weights = lines[0].split(' ')
    init_weight_a = int(init_weights[0])
    init_weight_b = int(init_weights[1])
    basket_weight_b = int(lines[1].split(' ')[1])
    basket_weight_a = int(lines[2].split(' ')[0])
    print '{0} {1}'.format(init_weight_a - basket_weight_a, init_weight_b - basket_weight_b)

if __name__ == '__main__':
    calc()

