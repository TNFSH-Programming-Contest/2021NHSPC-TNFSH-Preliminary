nothing:

all: arithmetic merge-pdf

arithmetic:
	cd Arithmetic && tps statement
	cd Arithmetic && tps gen

arithmetic-check:
	cd Arithmetic && > solution/check.txt
	cd Arithmetic && tps invoke solution/ac.cpp | tee -a solution/check.txt
	cd Arithmetic && tps invoke solution/wa.cpp | tee -a solution/check.txt
	cd Arithmetic && tps invoke solution/re.cpp | tee -a solution/check.txt
