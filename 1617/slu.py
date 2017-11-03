#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1617. Flat Spots
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
Yekaterinburg has an extensive network of tram routes. Trams of more than ten
routes go along some streets. It is clear that rails wear out quickly because
of such a load. Rails near tram stops sometimes are wavy. Many citizens hold
the city authorities responsible for such a poor state of tram railways: repair
works are carried out rarely, and even if rails are replaced, it is only by
cheapest ones—made of low-grade metal and with wooden ties.
However, not only authorities are guilty of this situation. Some tram drivers
are fans of fast driving, and they damage both rails and their trams. If a
tram accelerates to a high speed, say 80 kilometers per hour, and then brakes
sharply before a stop, it goes some distance skidding. This leads not only to
rail spoilage, but also to wearing out wheels at the places where they touch
rails. Flat spots emerge on the wheels, which cause pounding of the wheels,
rattle of the car, and further rail spoilage.
The administration of the tram depot decided to improve the situation by
servicing all trams that have wheels with flat spots. To remove flat spots,
wheels will be turned on a special lathe. Wheels from the same pair will be
decreased to equal size, but wheels from different pairs may become different
in size. To equip a car with wheels, repairmen must choose four wheel pairs
with equal wheel diameters.
Repairmen have finished turning all wheels. Some of them have become so small
that they can't be used anymore. Such wheels will be sent for remelting.
Instead of them, a stock of wheel pairs left from written-off cars can be used.
Repairmen have measured all wheel pairs that can be mounted to cars, and now
they need to know how many cars can be equipped.

[Input]
The first line contains the number n of available wheel pairs (1 ≤ n ≤ 150).
In the following n lines, diameters of wheels in millimeters are given (they
are integers in the range from 600 to 700).

[Output]
Output the number of cars that can be equipped with wheels using the given set
of wheel pairs.
'''

import sys;
import math;

def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')

def get_int_from_stdin():
    return int(get_str_from_stdin())

def calc():
    n = get_int_from_stdin()
    wheels = []
    while (n > 0):
        n = n - 1
        wheels.append(get_int_from_stdin())
    wheels.sort()
    d = 0
    c = 0
    r = 0
    for w in wheels:
        if (d == w):
            c = c + 1
            if (c == 4):
                r = r + 1
                c = 0
                d = 0
        else:
            d = w
            c = 1
    print r

if __name__ == '__main__':
    calc()

