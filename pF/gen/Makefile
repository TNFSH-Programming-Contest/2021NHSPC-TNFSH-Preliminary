TARGET = genmain.py

.PHONY: all debug clean

all:
	g++ -DEVAL -std=gnu++14 -O2 -pipe -static -s sol_debug.cpp -o sol_debug.exe
	python3.6 -OO ./genmain.py

d: debug
debug:
	g++ -DEVAL -std=gnu++14 -O3 -pipe -static -s sol_debug.cpp -o sol_debug.exe
	python3.6 ./genmain.py

clean:
	rm -rf manual
	rm -f sol_debug.exe

compile_outputs_list:
	@echo
