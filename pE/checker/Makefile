SOURCES := $(wildcard *.py)
EXECUTABLES := $(SOURCES:%.py=%.exe)

.PHONY: all clean

all: $(EXECUTABLES)

clean:
	rm -f *.exe

%.exe: %.py
	cp $< $@
	chmod +x $@

compile_outputs_list:
	@echo $(COMPILE_OUTPUTS)
