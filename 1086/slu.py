#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1086. Cryptography
Time limit: 2.0 second
Memory limit: 64 MB

[Description]
While preparing this problem set the jury has run into the following problem: it
was necessary to send by e-mail the texts of the problems. As it is well known,
e-mail is not reliable, messages are sent not enciphered, there is a danger that
someone can intercept them. The members of the program committee wanted no
participant know the texts of the problems before the start of the contest.
That's why they resorted to cryptography methods in order to save the texts of
the problems from an unsanctioned reading. The jury gas worked up a new way of
enciphering of a text. It is not patented yet, so it's kept secret. However,
we'll reveal you one secret: the new algorithm is based on the work with prime
numbers. In particular, in uses a calculation of n-th by order prime number.
Several members of the program committee independently have worked up programs
that make such calculations, but these programs produce different answers. Each
one of the programmers is sure that his program works correctly. That's why the
jury has reached the deadlock and can't continue working. The contest is about
not to take place.
You are to help to the jury and to save the contest. We want you to write a
program that calculates the n-th by order prime number. The main thing is that
your program should work correctly.

[Input]
First line contains a positive integer k. Then k positive integers follow (one
in each line). The numbers don't exceed 15000.

[Output]
For each number n you should output the n-th by order prime number. Each number
should be in its line.
'''

import sys
import math


def get_str_from_stdin():
    return sys.stdin.readline().strip('\r\n')


def get_int_from_stdin():
    try:
        s = get_str_from_stdin()
        return int(s)
    except ValueError:
        print 'Cannot convert from "{0}" to integer'.format(s)
        return None


__primes = []


def is_prime(n):
    if n in __primes:
        return True

    if n == 1 or n == 0:
        return False

    if n % 2 == 0:
        if n == 2:
            __primes.append(n)
            return True
        else:
            return False

    for p in __primes:
        if n % p == 0:
            return False

    __primes.append(n)
    return True


def find_primes(n):
    '''find first n primes'''
    is_prime(2)  # add first prime
    number = 3
    for i in range(2, n + 1):
        while not is_prime(number):
            number = number + 2
        number = number + 2


def calc():
    k = get_int_from_stdin()
    nth = []

    while k > 0:
        k = k - 1
        nth.append(get_int_from_stdin())

    max_nth = max(nth)
    find_primes(max_nth)

    for i in nth:
        print __primes[i - 1]


if __name__ == '__main__':
    calc()
