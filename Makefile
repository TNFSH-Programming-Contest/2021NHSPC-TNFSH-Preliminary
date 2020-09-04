nothing:

all: arithmetic merge-pdf

arithmetic:
	cd Arithmetic && tps statement
	cd Arithmetic && tps gen

arithmetic-check:
	cd Arithmetic && > solutions-check.txt
	cd Arithmetic && echo "ac.cpp" >> solutions-check.txt
	cd Arithmetic && tps invoke solution/ac.cpp | tee -a solutions-check.txt
	cd Arithmetic && echo "wa.cpp" >> solutions-check.txt
	cd Arithmetic && tps invoke solution/wa.cpp | tee -a solutions-check.txt
	cd Arithmetic && echo "re.cpp" >> solutions-check.txt
	cd Arithmetic && tps invoke solution/re.cpp | tee -a solutions-check.txt

merge-pdf:
	# 在problems.pdf前加入更多題本路徑
	pdfunite Arithmetic/statement/index.pdf problems.pdf
	# 將合併題本放到第一題的附檔，Arithmetic改成第一題的名稱
	mkdir -p Arithmetic/attachments
	cp problems.pdf Arithmetic/attachments
	# 99改成對應的比賽ID
	cmsImportTask -c 99 ./Arithmetic/ -u
