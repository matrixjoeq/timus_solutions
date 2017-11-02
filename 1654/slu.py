#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
1654. Cipher Message
Time limit: 1.0 second
Memory limit: 64 MB

[Description]
Müller tried to catch Stierlitz red-handed many times, but always failed because
Stierlitz could ever find some excuse. Once Stierlitz was looking through his
email messages. At that moment, Müller entered secretly and watched a meaningless
sequence of symbols appear on the screen. “A cipher message,” Müller thought.
“UTF-8,” Stierlitz thought.
It is known that Stierlitz ciphers messages by the following method.
1. He deletes all spaces and punctuation marks.
2. He replaces all successive identical letters by one such letter.
3. He inserts two identical letters at an arbitrary place many times.
Try to restore a message as it was after the second step. For that, remove from
the message all pairs of identical letters inserted at the third step.

[Input]
The only input line contains a message ciphered by Stierlitz. The message consists
of lowercase English letters and its length is at most 200000.

[Output]
Output the restored message.
'''

import sys;
import math;

def get_int_from_stdin():
    return int(sys.stdin.readline().strip('\r\n'))

def calc():
    msg = sys.stdin.readline().strip('\r\n')
    s = ''
    p = ''
    for c in msg:
        if (c != p):
            s = s + c
            p = c
        else:
            s = s[:-1]
            if (len(s) > 0):
                p = s[-1]
            else:
                p = ''
    print s

if __name__ == '__main__':
    calc()

