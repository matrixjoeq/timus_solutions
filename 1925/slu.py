#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1925. British Scientists Save the World
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
The world is in danger! Aliens threw a mysterious device to Earth n years ago.
Every year an unknown sign appeared on its screen and it started to make
threatening sounds until someone entered something on its keyboard. It lasted
till now. But recently British scientists have found out that this device is a
bomb which is capable to destroy our world in split second. The signs, which
the device displays on its screen, are numbers and for input the device expects
numbers as well.
The aliens invented a smart protection: every year, in order to avoid an explosion,
you had to enter a number, which is less than the number shown on the screen by
two. Fortunately, aliens decided that it takes a lot of computing resources to
check whether the input number is correct every year. That is why the test is
carried out once in n + 1 years. Moreover, they check only that the sum of all
numbers entered since the last test matches the expected one.
The good news is that all symbols, which the bomb showed, and all numbers, which
were entered, were recorded and the scientists already finished decrypting.
Recently a number k appeared on mysterious device's screen and the scientists
are sure that this time can be a fatal one. So, you have a chance to save the
world by finding out what number should be entered in order to avoid an explosion.

[Input]
The first line contains two positive integers n, k. In the next n lines there
are pairs of numbers bi, gi (bi is the number shown on device's screen, gi is
the number entered in the i-th year). All the integers in the input data do not
exceed 100.

[Output]
Output one nonnegative integer to save the world from the explosion. If there
is no such number output “Big Bang!”.
'''

import sys;
import math;

def calc():
    n, k = sys.stdin.readline().strip('\r\n').split(' ')
    n = int(n)
    k = int(k)


if __name__ == '__main__':
    calc()

