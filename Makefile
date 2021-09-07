nothing:

import-pA:
	cmsImportTask -c 6 ./pA/ -u $(if $(s), "" ,"--no-statement")

import-pB:
	cmsImportTask -c 6 ./pB/ -u $(if $(s), "" ,"--no-statement")

import-pC:
	cmsImportTask -c 6 ./pC/ -u $(if $(s), "" ,"--no-statement")

import-pD:
	cmsImportTask -c 6 ./pD/ -u $(if $(s), "" ,"--no-statement")

import-pE:
	cmsImportTask -c 6 ./pE/ -u $(if $(s), "" ,"--no-statement")

import-pF:
	cmsImportTask -c 6 ./pF/ -u $(if $(s), "" ,"--no-statement")
