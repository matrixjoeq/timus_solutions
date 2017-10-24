#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1880. Psych Up's Eigenvalues
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
At one of the contests at the Petrozavodsk Training Camp, players of the Psych
Up team quickly found the simple problem and Fedya sat at the computer. The
solution was ready in five minutes. Without spending time for testing, Fedya
submitted it and in a few seconds got Time Limit Exceeded.
Fedya crumpled the problem statement and left the room slamming the door behind
him. Things were going the wrong way and he needed to wind down. On his way to
the restroom Fedya heard a conversation of the contest authors. Pasha was
discussing with his friend the solution of the problem for which Fedya had got
TLE. Fedya could only discern the word “eigenvalues.”
Fedya thought about it and decided that he, for sure, had his eigenvalues. For
example, the date of birth, the number of his apartment, the mark he had got
at the latest exam, or the number of travels to contests. But they had a team
contest, so what was their team's eigenvalue? Of course, a number was a team's
eigenvalue if it was an eigenvalue for each of its players. With these joyful
thoughts Fedya returned to the contest room.

[Input]
The input data consist of three blocks two lines each. The first line of each
block contains the number n of a player's eigenvalues (1 ≤ n ≤ 4 000). In the
second line you are given n distinct integers in ascending order, which are
the eigenvalues. All the eigenvalues are positive integers not exceeding 10^9.

[Output]
Output the number of eigenvalues of the Psych Up team.
'''

import sys;
import math;

def get_individual_eigenvalues():
    n = int(sys.stdin.readline())
    line = sys.stdin.readline().strip('\r\n')
    return line.split(' ')

def pick_team_eigenvalues(team, player):
    if (len(team) == 0 or len(player) == 0):
        return []

    r = []
    idx_player = 0
    idx_team = 0
    while (idx_player < len(player) and idx_team < len(team)):
        if (int(player[idx_player]) == int(team[idx_team])):
            r.append(team[idx_team])
            idx_player = idx_player + 1
            idx_team = idx_team + 1
        elif (int(player[idx_player]) < int(team[idx_team])):
            idx_player = idx_player + 1
        else:
            idx_team = idx_team + 1

    return r

def calc():
    team = get_individual_eigenvalues()
    n = 2
    while (n > 0):
        player = get_individual_eigenvalues()
        team = pick_team_eigenvalues(team, player)
        n = n - 1

    print len(team)

if __name__ == '__main__':
    calc()

