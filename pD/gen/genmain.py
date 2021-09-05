#!/usr/bin/env python3

from pathlib  import Path
import random
import subprocess

from _gen  import runTest
from _gen.generator  import Generator, genStart
from _gen.present  import Entry, List, SpaceContainer, LineContainer

from genstruct  import randomInserted, randomSegments, genHills

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
		
		assert( 1 <= N <= 5*10**5 )
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
		
		assert( K <= 30 )
		
		return [N, K, V]
	
	return wrapfunc

def gen4(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		N, K, V = genfunc(**kwargs)
		
		assert( sum((1  if V[i]!=V[i-1] else 0)  for i in range(1, N)) <= 2 )
		assert( K <= 2000 )
		
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

###################################################################################

@gen1
def gen1Random():
	N = random.randint(250, 300)
	K = random.randint(1, 10**9)
	V = random.choices(range(1, 10**9+1), k=N)
	
	return [N, K, V]

@gen1
def gen1RandHill(**kwargs):
	N = random.randint(250, 300)
	K = random.randint(8*10**8, 10**9)
	V = genHills(N, K, **kwargs)
	
	return [N, K, V]

@gen1
def gen1RandHighHill(**kwargs):
	N = random.randint(250, 300)
	K = 981455877
	V = genHills(N, K, th=49/50, hlim=(109050653, 109050653), llim=(1, 100), **kwargs)
	
	return [N, K, V]

@gen1
def gen1Segments(K=999988679, v=[9769]):
	N = random.randint(250, 300)
	V = randomSegments(N, v)
	
	return [N, K, V]

###################################################################################

@gen2
def gen2Random():
	N = random.randint(6000, 8000)
	K = random.randint(1, 10**9)
	V = random.choices(range(1, 10**9+1), k=N)
	
	return [N, K, V]

@gen2
def gen2RandHill(**kwargs):
	N = random.randint(6000, 8000)
	K = random.randint(8*10**8, 10**9)
	V = genHills(N, K, **kwargs)
	
	return [N, K, V]

@gen2
def gen2RandHighHill(**kwargs):
	N = random.randint(6000, 8000)
	K = 995572270
	V = genHills(N, K, th=499/500, hlim=(9050657, 9050657), llim=(1, 30), **kwargs)
	
	return [N, K, V]

@gen2
def gen2Segments(K=999988679, v=[9769]):
	N = random.randint(6000, 8000)
	V = randomSegments(N, v)
	
	return [N, K, V]

###################################################################################

@gen3
def gen3Random():
	N = random.randint(4*10**5, 5*10**5)
	K = random.randint(1, 30)
	V = random.choices(range(1, 10**9+1), k=N)
	
	return [N, K, V]

@gen3
def gen3Stairs(**kwargs):
	N = random.randint(4*10**5, 5*10**5)
	K = 27
	V = random.choices([3, 9, 18, 27], k=N)
	
	return [N, K, V]

@gen3
def gen3Isolated(K=30, lcnt=3):
	N = random.randint(4*10**5, 5*10**5)
	V = randomInserted([15]*(N-lcnt), [1]*lcnt)
	
	return [N, K, V]

###################################################################################

@gen4
def gen4Random():
	N = random.randint(4*10**5, 5*10**5)
	K = random.randint(1, 2000)
	V = randomSegments(N, random.sample(range(1, 10**9+1), 3))
	
	return [N, K, V]

@gen4
def gen4Stairs(part=3):
	N = random.randint(4*10**5, 5*10**5)
	K = random.randint(1500, 2000)
	
	step = random.choice(range(7, 500))
	V = randomSegments(N, random.sample(range(step, 10**9+1, step), part))
	
	return [N, K, V]

@gen4
def gen4Segment(K=1995, v=[35, 133, 95]):
	# [25, 125, 35]
	# [15, 160, 15]
	N = random.randint(4*10**5, 5*10**5)
	
	S1 = N // 3
	S1 += S1 % (K // v[1]) + 1
	
	S0 = (N - S1) // 2
	S2 = N - S0 - S1
	
	# randomSegments(N, v)
	V = []
	V.extend([v[0]]*S0)
	V.extend([v[1]]*S1)
	V.extend([v[2]]*S2)
	
	return [N, K, V]

###################################################################################

@genAll
def gen5Random():
	N = random.randint(4*10**5, 5*10**5)
	K = random.randint(1, 10**9)
	V = random.choices(range(1, 10**9+1), k=N)
	
	return [N, K, V]

@genAll
def gen5RandHill(**kwargs):
	N = random.randint(4*10**5, 5*10**5)
	K = random.randint(8*10**8, 10**9)
	V = genHills(N, K, **kwargs)
	
	return [N, K, V]

@genAll
def gen5RandHighHill(**kwargs):
	N = random.randint(int(4.5*10**5), 5*10**5)
	K = 981456300
	V = genHills(N, K, th=399999/400000, hlim=(109050700, 109050700), llim=(1, 30), **kwargs)
	
	return [N, K, V]

@genAll
def gen5Isolated(lx=1819):
	N = random.randint(4*10**5, 5*10**5)
	K = 999998888
	
	V = randomInserted([549752]*(N-lx+1), [1]*(lx-1))
	
	return [N, K, V]

@genAll
def gen5Segments(K=999988679, v=[1999]):
	# [9769]
	N = random.randint(4*10**5, 5*10**5)
	V = randomSegments(N, v)
	
	return [N, K, V]

def genMain():
	# random.seed(20210828 ** 2231)
	random.seed(20210905 ** 1751)
	
	test_format = str('manual/{subtask}-{testid:0>2}.{ext}')
	
	gen = TestGenerator()
	gen.config(debug=False, test_format=test_format)
	
	print('[genMain]: Gen #samples')
	gen.newTest('samples', 1, genSample1)
	gen.newTest('samples', 1, genSample2)
	gen.newTest('samples', 1, genSample3)
	
	print('[genMain]: Gen #sub1')
	gen.newTest('sub1', 3, gen1Random)
	gen.newTest('sub1', 2, gen1RandHill)
	gen.newTest('sub1', 2, gen1RandHighHill)
	gen.newTest('sub1', 1, gen1Segments)
	
	print('[genMain]: Gen #sub2')
	gen.newTest('sub2', 3, gen2Random)
	gen.newTest('sub2', 2, gen2RandHill)
	gen.newTest('sub2', 2, gen2RandHighHill)
	gen.newTest('sub2', 1, gen2Segments)
	
	print('[genMain]: Gen #sub3')
	gen.newTest('sub3', 3, gen3Random)
	gen.newTest('sub3', 2, gen3Stairs)
	gen.newTest('sub3', 2, gen3Isolated)
	gen.newTest('sub3', 1, gen3Isolated, opt_gen=dict(lcnt=14))
	
	print('[genMain]: Gen #sub4')
	gen.newTest('sub4', 3, gen4Random)
	gen.newTest('sub4', 2, gen4Stairs)
	gen.newTest('sub4', 1, gen4Stairs, opt_gen=dict(part=1))
	gen.newTest('sub4', 1, gen4Segment)
	gen.newTest('sub4', 1, gen4Segment, opt_gen=dict(K=1992, v=[24, 249, 664]))
	gen.newTest('sub4', 1, gen4Segment, opt_gen=dict(K=1848, v=[168, 264, 77]))
	
	print('[genMain]: Gen #all')
	gen.newTest('all', 2, gen5Random)
	gen.newTest('all', 1, gen5RandHill, opt_gen=dict(th=9999/10000, nsth=.0015, llim=(1, 15)))
	gen.newTest('all', 1, gen5RandHill, opt_gen=dict(th=19999/20000, llim=(1, 5)))
	gen.newTest('all', 1, gen5RandHighHill)
	gen.newTest('all', 1, gen5Isolated)
	gen.newTest('all', 1, gen5Isolated, opt_gen=dict(lx=3))
	gen.newTest('all', 1, gen5Segments)
	gen.newTest('all', 1, gen5Segments, opt_gen=dict(K=161438597, v=[102019]))
	
	
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
		for subtask in ['samples', 'sub1', 'sub2', 'sub3', 'sub4', 'all']:
			gendata.write('@subtask {}\n'.format(subtask))
			for inpath in caseMap[subtask]:
				gendata.write('manual {}\n'.format(inpath))
			
			gendata.write('\n')

if __name__ == "__main__":
	genStart(genMain)