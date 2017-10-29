#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1991. The battle near the swamp
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
In the battle with the Trade Federation, Queen Amidala decided to ask gungans
for help. Jar Jar Binks escorted the Queen and her people to the holy place
where they had an agreement. The gungans agreed to provide their army in order
to get the droids of the Federation out from the capital. The gungan ruler Boss
Nass was so grateful for uniting the nations that he appointed Jar Jar a general.
And here they are: two armies lined up along the bank of the swamp. The droids
of the Federation are well-disciplined soldiers. They stand in neat formation,
divided into n blocks of k droids each. The gungans have a foolproof weapon
against droids, which is small energy balls called boom booms. One such ball
can disable exactly one droid.
Jar Jar Binks also decided to split his army into n parts and give each part a
task to destroy the corresponding block of droids. Each part received a truck
with boom booms. Now help general Binks calculate the number of boom booms that
will be left unused and the number of droids that will survive the attack. You
can assume that when a boom boom is fired at a droid by a gungan, it always hits
the target.

[Input]
The first line of the input contains numbers n and k (1 ≤ n, k ≤ 10 000). The
second line contains n numbers ai (0 ≤ ai ≤ 100 000) — the number of boom-booms
in the i-th truck.

[Output]
Print two integers — the number of unused boom booms and the number of survived
droids.
'''

import sys;
import math;

def calc():
    n, k = sys.stdin.readline().strip('\r\n').split(' ')
    n = int(n)
    k = int(k)
    booms = sys.stdin.readline().strip('\r\n').split(' ')
    unused_booms = 0
    survived_droids = 0
    for i in booms:
        i = int(i)
        if (i > k):
            unused_booms = unused_booms + i - k
        elif (i < k):
            survived_droids = survived_droids + k - i

    print '{0} {1}'.format(unused_booms, survived_droids)

if __name__ == '__main__':
    calc()

