#!/usr/bin/env python3
with open('manual/0.in', 'w') as file:
	file.write('-42 * 9')

with open('data', 'w') as file:
	file.write("@subtask all\n")
	file.write("manual 0.in")
