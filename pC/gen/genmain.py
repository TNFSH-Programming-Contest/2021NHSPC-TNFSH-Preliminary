#!/usr/bin/env python3.6

from pathlib  import Path
import random
import subprocess

from _gen  import runTest
from _gen.generator  import Generator, genStart
from _gen.present  import Entry, List, SpaceContainer, LineContainer

from genstruct  import genRandomize, genAlternate

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
	def wrapfunc(**kwargs):
		Q, Qs = genfunc(**kwargs)
		
		assert( 1 <= Q <= 10**6 )
		assert( len(Qs) == Q )
		for qx, *qxv in Qs:
			assert( qx in [1, 2, 3] )
			if qx == 1:
				assert( len(qxv) == 1 )
				
				k, = qxv
				assert( -10000 <= k <= 10000 )
			elif qx == 2:
				assert( len(qxv) == 3 )
				
				i, op, y = qxv
				assert( i in [1, 2] )
				assert( op in ['+', '*'] )
				assert( -100 <= y <= 100 )
			elif qx == 3:
				pass
		
		# native assert
		return [Q, Qs]
	
	return wrapfunc

def gen1(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		Q, Qs = genfunc(**kwargs)
		
		assert( Q <= 8000 )
		for qx, *qxv in Qs:
			assert( qx != 3 )
		
		return [Q, Qs]
	
	return wrapfunc

def gen2(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		Q, Qs = genfunc(**kwargs)
		
		for qx, *qxv in Qs:
			if qx == 2:
				i, op, y = qxv
				assert( op == '+' )
		
		return [Q, Qs]
	
	return wrapfunc

def gen3(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		Q, Qs = genfunc(**kwargs)
		
		for qx, *qxv in Qs:
			if qx == 1:
				k, = qxv
				assert( 0 <= k <= 1 )
			
			assert( qx != 3 )
		
		return [Q, Qs]
	
	return wrapfunc

def gen4(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		Q, Qs = genfunc(**kwargs)
		
		for qx, *qxv in Qs:
			assert( qx != 3 )
		
		return [Q, Qs]
	
	return wrapfunc

@genAll
def genSample1():
	return \
	[
		8,
		[
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
	return \
	[
		9,
		[
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

@gen1
def gen1Random(**kwargs):
	Q = random.randint(7000, 8000)
	return [Q, genRandomize(Q, qxweight=(1, 1, 0), **kwargs)]

@gen1
def gen1Alter(**kwargs):
	Q = random.randint(7700, 8000)
	return [Q, genAlternate(Q, has3=False, **kwargs)]

@gen2
def gen2Random(**kwargs):
	Q = random.randint(800000, 10**6)
	return [Q, genRandomize(Q, qxweight=(1, 1, 1), opweight=(1, 0), **kwargs)]

@gen2
def gen2Alter(**kwargs):
	Q = random.randint(950000, 10**6)
	return [Q, genAlternate(Q, opweight=(1, 0), **kwargs)]

@gen3
def gen3Random(**kwargs):
	Q = random.randint(800000, 10**6)
	return [Q, genRandomize(Q, krange=(0, 1), qxweight=(1, 1, 0), **kwargs)]

@gen3
def gen3Alter(**kwargs):
	Q = random.randint(950000, 10**6)
	return [Q, genAlternate(Q, krange=(0, 1), has3=False, **kwargs)]

@gen4
def gen4Random(**kwargs):
	Q = random.randint(800000, 10**6)
	return [Q, genRandomize(Q, qxweight=(1, 1, 0), **kwargs)]

@gen4
def gen4Alter(**kwargs):
	Q = random.randint(950000, 10**6)
	return [Q, genAlternate(Q, has3=False, **kwargs)]

@genAll
def gen5Random(**kwargs):
	Q = random.randint(800000, 10**6)
	return [Q, genRandomize(Q, **kwargs)]

@genAll
def gen5Alter(**kwargs):
	Q = random.randint(950000, 10**6)
	return [Q, genAlternate(Q, **kwargs)]

def genMain():
	random.seed(20210828**1327)
	
	test_format = str(GENDIR.resolve() / 'manual' / '{subtask}-{testid:0>2}.{ext}')
	
	gen = TestGenerator()
	gen.config(debug=False, test_format=test_format)
	
	print('[genMain]: Gen #samples')
	gen.newTest('samples', 1, genSample1)
	gen.newTest('samples', 1, genSample2)
	
	print('[genMain]: Gen #sub1')
	gen.newTest('sub1', 3, gen1Random)
	gen.newTest('sub1', 2, gen1Alter)
	gen.newTest('sub1', 1, gen1Alter, opt_gen=dict(opweight=(1, 100)))
	gen.newTest('sub1', 1, gen1Alter, opt_gen=dict(opweight=(100, 1)))
	
	print('[genMain]: Gen #sub2')
	gen.newTest('sub2', 3, gen2Random)
	gen.newTest('sub2', 3, gen2Alter)
	
	print('[genMain]: Gen #sub3')
	gen.newTest('sub3', 3, gen3Random)
	gen.newTest('sub3', 2, gen3Alter)
	gen.newTest('sub3', 1, gen3Alter, opt_gen=dict(opweight=(1, 100)))
	gen.newTest('sub3', 1, gen3Alter, opt_gen=dict(opweight=(100, 1)))
	
	print('[genMain]: Gen #sub4')
	gen.newTest('sub4', 3, gen4Random)
	gen.newTest('sub4', 2, gen4Alter)
	gen.newTest('sub4', 1, gen4Alter, opt_gen=dict(opweight=(1, 100)))
	gen.newTest('sub4', 1, gen4Alter, opt_gen=dict(opweight=(100, 1)))
	
	print('[genMain]: Gen #all')
	gen.newTest('all', 3, gen5Random)
	gen.newTest('all', 1, gen5Random, opt_gen=dict(qxweight=(10, 10, 1)))
	gen.newTest('all', 1, gen5Random, opt_gen=dict(qxweight=(1, 1, 3)))
	gen.newTest('all', 2, gen5Alter)
	gen.newTest('all', 1, gen5Alter, opt_gen=dict(opweight=(1, 100)))
	gen.newTest('all', 1, gen5Alter, opt_gen=dict(opweight=(100, 1)))
	
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