#!/usr/bin/env python3.6

import os
print('#', os.getcwd())

from pathlib  import Path
import subprocess

from _gen  import runTest
from _gen.generator  import Generator, genStart
from _gen.present  import Entry, List, SpaceContainer, LineContainer


GENDIR = Path(__file__).resolve().parent

class TestGenerator(Generator):
	def presentTest(self):
		return List([
			Entry(end='\n'),
			LineContainer(
				SpaceContainer()
			)
		])
	
	def presentAns(self):
		return LineContainer()
	
	def nativeSolve(self, file):
		solution = str(GENDIR / 'sol_debug.exe')
		# proc = subprocess.run([solution], stdin=file, capture_output=True, check=True)
		proc = subprocess.run([solution], stdin=file, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
		ans = proc.stdout.decode().strip()
		
		if proc.stderr:
			print('[sol_debug]: {}'.format(proc.stderr.decode()))
		
		return [*ans.split('\n')]
	
	def newTest(self, *args, **kwargs):
		super().newTest(*args, **kwargs, native_solve=True)

def genAll(genfunc):
	def wrapfunc():
		Q, Qs = genfunc()
		
		assert( 1 <= Q <= 10**6 )
		for qx, *qxv in Qs:
			assert( qx in [1, 2, 3] )
			if qx == 1:
				k, = qxv
				assert( -10000 <= k <= 10000 )
			elif qx == 2:
				i, op, y = qxv
				assert( i in [1, 2] )
				assert( op in ['+', '*'] )
				assert( -100 <= y <= 100 )
			elif qx == 3:
				pass
		
		# native assert
		return [Q, Qs]
	
	return wrapfunc

@genAll
def gen1(genfunc):
	def wrapfunc():
		Q, Qs = genfunc()
		
		assert( Q <= 8000 )
		for qx, *qxv in Qs:
			assert( qx != 3 )
		
		return [Q, Qs]
	
	return wrapfunc

@genAll
def gen2(genfunc):
	def wrapfunc():
		Q, Qs = genfunc()
		
		for qx, *qxv in Qs:
			if qx == 2:
				i, op, y = qxv
				assert( op == '+' )
		
		return [Q, Qs]
	
	return wrapfunc

@genAll
def gen3(genfunc):
	def wrapfunc():
		Q, Qs = genfunc()
		
		for qx, *qxv in Qs:
			if qx == 1:
				k, = qxv
				assert( 0 <= k <= 1 )
			
			assert( qx != 3 )
		
		return [Q, Qs]
	
	return wrapfunc

@genAll
def gen4(genfunc):
	def wrapfunc():
		Q, Qs = genfunc()
		
		for qx, *qxv in Qs:
			assert( qx != 3 )
		
		return [Q, Qs]
	
	return wrapfunc

@genAll
def genSample1():
	return [
		8, [
			[1, 3],
			[2, 1, '+', 2],
			[1, 3],
			[2, 2, '*', 2],
			[1, 3],
			[2, 1, '+', 2],
			[1, 3],
			[3],
		]
	]

@genAll
def genSample2():
	return [
		9, [
			[1, 3],
			[2, 1, '*', 0],
			[1, 3],
			[3],
			[2, 2, '*', 0],
			[1, 3],
			[3],
			[2, 1, '+', 2],
			[3]
		]
	]

def genMain():
	test_format = str(GENDIR.resolve() / 'manual' / '{subtask}-{testid}.{ext}')
	
	gen = TestGenerator()
	gen.config(debug=False, test_format=test_format)
	
	gen.newTest('samples', 1, genSample1)
	gen.newTest('samples', 1, genSample2)
	
	# sub1 sub2 sub3 sub4 all
	
	runTest.config(test_dir=str(GENDIR.resolve() / 'manual'))
	with open('data', 'w') as gendata:
		caseMap = {}
		for cprefix, cin, cout in runTest.getCases():
			inpath = Path(cin).name
			subtask, *_ = inpath.split('-')
			if not subtask in caseMap:
				caseMap[subtask] = []
			
			caseMap[subtask].append(str(inpath))
		
		print(caseMap)
		for subtask in caseMap:
			gendata.write('@subtask {}\n'.format(subtask))
			for inpath in caseMap[subtask]:
				gendata.write('manual {}\n'.format(inpath))
			
			gendata.write('\n')

if __name__ == "__main__":
	genStart(genMain)