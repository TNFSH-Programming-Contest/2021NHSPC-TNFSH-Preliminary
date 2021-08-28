#!/usr/bin/env python3

from pathlib  import Path
import random
import subprocess

from _gen  import runTest
from _gen.generator  import Generator, genStart
from _gen.present  import Entry, List, SpaceContainer, LineContainer

from genstruct  import randomInserted, randomSegment

class TestGenerator(Generator):
	def presentTest(self):
		return List([
			Entry(end=' '), Entry(end='\n'),
			SpaceContainer(end='\n')
		])
	
	def presentAns(self):
		return Entry(end='\n')
	
	def nativeSolve(self, file):
		solution = './sol_debug.exe'
		# proc = subprocess.run([solution], stdin=file, capture_output=True, check=True)
		proc = subprocess.run([solution], stdin=file, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
		ans = proc.stdout.decode().strip()
		
		if proc.stderr:
			print('[sol_debug]: {}'.format(proc.stderr.decode()))
		
		return int(ans)
	
	def newTest(self, *args, **kwargs):
		super().newTest(*args, **kwargs, native_solve=True)

def genAll(genfunc):
	def wrapfunc(**kwargs):
		N, K, V = genfunc(**kwargs)
		
		assert( 1 <= N <= 2*10**6 )
		assert( 1 <= K <= 10**9 )
		
		assert( len(V) == N )
		assert( all(1 <= ai <= 10**9  for ai in V) )
		
		return [N, K, V]
	
	return wrapfunc

def gen1(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		N, K, V = genfunc(**kwargs)
		
		assert( N <= 300 )
		
		return [N, K, V]
	
	return wrapfunc

def gen2(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		N, K, V = genfunc(**kwargs)
		
		assert( N <= 8000 )
		
		return [N, K, V]
	
	return wrapfunc

def gen3(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		N, K, V = genfunc(**kwargs)
		
		assert( K <= 10 )
		
		return [N, K, V]
	
	return wrapfunc

def gen4(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		N, K, V = genfunc(**kwargs)
		
		assert( sum((1  if V[i]!=V[i-1] else 0)  for i in range(1, N)) <= 2 )
		assert( K <= 500 )
		
		return [N, K, V]
	
	return wrapfunc

@genAll
def genSample1():
	return \
	[
		5, 5,
		[1, 1, 1, 1, 1]
	]

@genAll
def genSample2():
	return \
	[
		7, 11,
		[3, 3, 5, 7, 7, 8, 8]
	]

@genAll
def genSample3():
	return \
	[
		5, 5,
		[1, 2, 3, 2, 1]
	]

def genMain():
	random.seed(20210828 ** 2231)
	
	test_format = str('manual/{subtask}-{testid:0>2}.{ext}')
	
	gen = TestGenerator()
	gen.config(debug=False, test_format=test_format)
	
	print('[genMain]: Gen #samples')
	gen.newTest('samples', 1, genSample1)
	gen.newTest('samples', 1, genSample2)
	gen.newTest('samples', 1, genSample3)
	
	runTest.config(test_dir='manual')
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