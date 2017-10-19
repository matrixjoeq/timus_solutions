#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
2023. Donald is a postman
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Donald Duck works as a postman for the Walt Disney Studios. He delivers
children’s letters from all over the world to his friends, which are
cartoon characters. The Studios has three cases for the letters, with
nine sections in each case. Every section has the name of the receiver
on it. All cases stand in a row as it is shown at the picture below.
Donald Duck have brought n letters today. Initially, he stands near the
leftmost case. He has to make one step to go to the neighboring case or
to the previous one. How many steps will he make until he puts all the
letters into the respective sections, if he does this in the order they
are in his bag?

----------------------------  ----------------------------  ---------------------------
| Alice   | Ariel | Aurora |  | Bambi  | Belle  | Bolt   |  | Dumbo  | Genie | Jiminy |
----------------------------  ----------------------------  ---------------------------
| Phil    | Peter | Olaf   |  | Mulan  | Mowgli | Mickey |  | Kuzko  | Kida  | Kenai  |
----------------------------  ----------------------------  ---------------------------
| Phoebus | Ralph | Robin  |  | Silver | Simba  | Stitch |  | Tarzan | Tiana | Winnie |
----------------------------  ----------------------------  ---------------------------

[Input]
The first line contains an integer n that is the amount of letters in
Donald’s bag (1 ≤ n ≤ 1000). The following n lines contain receivers of
the letters in the order they are in the bag.

[Output]
Output the number of steps Donald should make to put all the letters
into the cases.
'''

import sys;
import math;

def calc():
    cases = (('Alice'  , 'Ariel' , 'Aurora',
              'Phil'   , 'Peter' , 'Olaf'  ,
              'Phoebus', 'Ralph' , 'Robin' ),
             ('Bambi'  , 'Belle' , 'Bolt'  ,
              'Mulan'  , 'Mowgli', 'Mickey',
              'Silver' , 'Simba' , 'Stitch'),
             ('Dumbo'  , 'Genie' , 'Jiminy',
              'Kuzko'  , 'Kida'  , 'Kenai' ,
              'Tarzan' , 'Tiana' , 'Winnie'))
    n = int(sys.stdin.readline())
    names = []
    while (n > 0):
        names.append(sys.stdin.readline().strip('\r\n'))
        n = n - 1

    steps = 0
    pos = 0
    new_pos = 0
    for name in names:
        for i in range(3):
            if (name in cases[i]):
                new_pos = i
                break
        steps = steps + abs(pos - new_pos)
        pos = new_pos
    print steps

if __name__ == '__main__':
    calc()

