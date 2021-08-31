#!/usr/bin/env python3

import sys

with open(sys.argv[2]) as f:
    Answer = float(f.readline())

with open(sys.argv[3]) as f:
    Output = float(f.readline())

Ae = abs(Answer-Output)
Re = Ae/Answer

if Ae <= 0.000001 or Re <= 0.000001:
    print("1.0")
else:
    print("0.0")