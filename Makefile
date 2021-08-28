nothing:

all: pA merge-pdf

pA:
	cd pA && tps statement
	cd pA && tps gen

pA-check:
	cd pA && > solutions-check.txt
	cd pA && echo "ac.cpp" >> solutions-check.txt
	cd pA && tps invoke solution/ac.cpp | tee -a solutions-check.txt

merge-pdf:
	pdfunite pA/statement/index.pdf problems.pdf
	mkdir -p pA/attachments
	cp problems.pdf pA/attachments
	# 99改成對應的比賽ID
	cmsImportTask -c 99 ./pA/ -u
