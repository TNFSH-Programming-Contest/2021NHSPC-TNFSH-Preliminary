#!/usr/bin/env python3

import sys

try:
    with open(sys.argv[2]) as f:
        Answer = f.read()

    with open(sys.argv[3]) as f:
        Output = f.read()

    Answer = Answer.rstrip()
    Output = Output.rstrip()

    if Answer == Output:
        print("1.0")
        print("Output is correct", file=sys.stderr)
    else:
        print("0.0")
        print("Output isn't correct", file=sys.stderr)
except:
    print("0.0")
    print("Checker Error", file=sys.stderr)
