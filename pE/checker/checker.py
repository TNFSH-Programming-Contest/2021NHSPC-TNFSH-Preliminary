#!/usr/bin/env python3

import sys

with open(sys.argv[2]) as f:
    Answer = float(f.readline())

with open(sys.argv[3]) as f:
    try:
        Output = float(f.readline())
    except:
        print("0.0")
        print("Output isn't correct", file=sys.stderr)
        exit(0)

try:
    Ae = abs(Answer-Output)
    Re = Ae/Answer

    if Ae <= 0.000001 or Re <= 0.000001:
        print("1.0")
        print("Output is correct", file=sys.stderr)
    else:
        print("0.0")
        print("Output isn't correct", file=sys.stderr)
except:
    print("0.0")
    print("Checker Error", file=sys.stderr)
