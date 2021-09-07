from pathlib import Path

import random
import subprocess
from math import log

from _gen import runTest
from _gen.generator  import Generator, genStart
from _gen.present  import Entry, List, SpaceContainer, LineContainer

GENDIR = Path(__file__).resolve().parent

class TestGenerator(Generator):
	def presentTest(self):
		return List(
			[
				List([
					Entry(end=' '),
					Entry(end='\n')
				]),
				SpaceContainer(end='\n')
			]
		)
	
	def presentAns(self):
		return List(
			[SpaceContainer()]
		)
	
	def nativeSolve(self, file):
		solver = str(GENDIR / 'sol_debug.exe')
		proc = subprocess.run([solver], stdin=file, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
		ans = proc.stdout.decode().strip()
		
		if proc.stderr:
			print('[solver]: {}'.format(proc.stderr.decode()))

		ans = ans.split()
		
		return [ans]
	
	def postProcess(self, test):
		return
	
	def newTest(self, *args, **kwargs):
		super().newTest(*args, **kwargs, native_solve=True)

MAXN = 200000
MINA = -1000000000
MAXA = 1000000000

def genAll(genfunc):
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		assert(1 <= N <= MAXN)
		assert(len(A) == N)
		assert(1 <= K <= N)
		for a in A:
			assert(MINA <= a <= MAXA)
		
		return [[N, K], A]
	
	return wrapfunc

############################## Gen 0 ##############################

def gen0(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		return [N, K, A]
	
	return wrapfunc

@gen0
def gen0A():
	return [
		5, 2, [3, 2, -2, -1, 0]
	]

@gen0
def gen0B():
	return [
		5, 3, [-3, 3, 0, 2, -3]
	]

@gen0
def gen0C():
	return [
		5, 4, [-3, -1, -3, -1, -2]
	]

@gen0
def gen0D():
	return [
		10, 2, [7, 9, 1, 7, 9, 3, 3, 1, 5, 5]
	]

############################## Gen 1 ##############################

def gen1(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		assert(1 <= N <= 1000)
		return [N, K, A]
	
	return wrapfunc

@gen1
def gen1A():
	N = random.randint(1, 1000)
	K = random.randint(1, N)
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen1
def gen1B():
	N = random.randint(950, 1000)
	K = random.randint(1, N)
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen1
def gen1C():
	N = random.randint(950, 1000)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(-2, 2))
	
	return [N, K, A]

############################## Gen 2 ##############################

def gen2(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		assert(K == 1)
		return [N, K, A]
	
	return wrapfunc

@gen2
def gen2A():
	N = random.randint(1, MAXN)
	K = 1
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen2
def gen2B():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = 1
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

############################## Gen 3 ##############################

def gen3(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		assert(K == N)
		sorted_A = sorted(A)
		for i in range(1, len(A)):
			assert(sorted_A[i - 1] != sorted_A[i])
		return [N, K, A]
	
	return wrapfunc

@gen3
def gen3A():
	N = random.randint(1, MAXN)
	K = N
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))
	
	random.shuffle(A)

	return [N, K, A]

@gen3
def gen3B():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = N
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))
	
	random.shuffle(A)

	return [N, K, A]

############################## Gen 4 ##############################

def gen4(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		assert(K == N)
		return [N, K, A]
	
	return wrapfunc

@gen4
def gen4A():
	N = random.randint(1, MAXN)
	K = N
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	return [N, K, A]

@gen4
def gen4B():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = N
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	return [N, K, A]

@gen4
def gen4C():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = N
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	times = random.randint(int(.095 * N), int(.1 * N))

	for t in range(times):
		d = random.randint(1, K - 1)
		id = random.randint(0, N - d - 1)
		A[id + d] = A[id]

	return [N, K, A]

@gen4
def gen4D():
	N = random.randint(95, 100)
	K = N
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	times = random.randint(int(.095 * N), int(.1 * N))

	for t in range(times):
		d = random.randint(1, K - 1)
		id = random.randint(0, N - d - 1)
		A[id + d] = A[id]

	return [N, K, A]

@gen4
def gen4E():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = N
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	times = random.randint(int(.475 * N), int(.5 * N))

	for t in range(times):
		d = random.randint(1, K - 1)
		id = random.randint(0, N - d - 1)
		A[id + d] = A[id]

	return [N, K, A]

############################## Gen 5 ##############################

def gen5(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		assert(K == 2)
		sorted_A = sorted(A)
		for i in range(1, len(A)):
			assert(sorted_A[i - 1] != sorted_A[i])
		return [N, K, A]
	
	return wrapfunc

@gen5
def gen5A():
	N = random.randint(1, MAXN)
	K = 2
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))
	
	random.shuffle(A)

	return [N, K, A]

@gen5
def gen5B():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = 2
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))
	
	random.shuffle(A)

	return [N, K, A]

############################## Gen 6 ##############################

def gen6(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		assert(K == 2)
		return [N, K, A]
	
	return wrapfunc

@gen6
def gen6A():
	N = random.randint(1, MAXN)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	return [N, K, A]

@gen6
def gen6B():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	return [N, K, A]

@gen6
def gen6C():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	times = random.randint(int(.095 * N), int(.1 * N))

	for t in range(times):
		d = random.randint(1, K - 1)
		id = random.randint(0, N - d - 1)
		A[id + d] = A[id]

	return [N, K, A]

@gen6
def gen6D():
	N = random.randint(95, 100)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	times = random.randint(int(.095 * N), int(.1 * N))

	for t in range(times):
		d = random.randint(1, K - 1)
		id = random.randint(0, N - d - 1)
		A[id + d] = A[id]

	return [N, K, A]

@gen6
def gen6E():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	random.shuffle(A)

	times = random.randint(int(.475 * N), int(.5 * N))

	for t in range(times):
		d = random.randint(1, K - 1)
		id = random.randint(0, N - d - 1)
		A[id + d] = A[id]

	return [N, K, A]

############################## Gen 7 ##############################

def gen7(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		for i in range(1, len(A)):
			assert(A[i - 1] < A[i])
		return [N, K, A]
	
	return wrapfunc

@gen7
def gen7A():
	N = random.randint(1, MAXN)
	K = random.randint(3, N - 1)
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))

	return [N, K, A]

@gen7
def gen7B():
	N = random.randint(1, MAXN)
	K = N
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))

	return [N, K, A]

@gen7
def gen7C():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = random.randint(3, N - 1)
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))

	return [N, K, A]

############################## Gen 8 ##############################

def gen8(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		for i in range(1, len(A)):
			assert(A[i - 1] <= A[i])
		return [N, K, A]
	
	return wrapfunc

@gen8
def gen8A():
	N = random.randint(1, MAXN)
	K = random.randint(3, N - 1)
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))

	times = random.randint(int(.475 * MAXN), int(.5 * MAXN))

	for t in range(times):
		id = random.randint(0, N - 2)
		A[id + 1] = A[id]

	return [N, K, A]

@gen8
def gen8B():
	N = random.randint(1, MAXN)
	K = N
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))

	times = random.randint(int(.475 * MAXN), int(.5 * MAXN))

	for t in range(times):
		id = random.randint(0, N - 2)
		A[id + 1] = A[id]

	return [N, K, A]

@gen8
def gen8C():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = random.randint(3, N - 1)
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))

	times = random.randint(int(.475 * MAXN), int(.5 * MAXN))

	for t in range(times):
		id = random.randint(0, N - 2)
		A[id + 1] = A[id]

	return [N, K, A]

@gen8
def gen8D():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = 2
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(-2, 2))
	A.sort()
	return [N, K, A]

############################## Gen 9 ##############################

def gen9(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		sorted_A = sorted(A)
		for i in range(1, len(A)):
			assert(sorted_A[i - 1] != sorted_A[i])
		return [N, K, A]
	
	return wrapfunc

@gen9
def gen9A():
	N = random.randint(1, MAXN)
	K = random.randint(1, N)
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))
	
	random.shuffle(A)

	return [N, K, A]

@gen9
def gen9B():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = random.randint(1, N)
	A = [random.randint(MINA, MAXA - N)]
	for i in range(1, N):
		A.append(random.randint(A[i - 1] + 1, MAXA - N + i))
	
	random.shuffle(A)

	return [N, K, A]

############################## Gen 10 ##############################

def gen10(genfunc):
	@genAll
	def wrapfunc(**kwargs):
		[N, K, A] = genfunc(**kwargs)
		return [N, K, A]
	
	return wrapfunc

@gen10
def gen10A():
	N = random.randint(1, MAXN)
	K = 1
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen10
def gen10B():
	N = random.randint(1, MAXN)
	K = N
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen10
def gen10C():
	N = random.randint(1, MAXN)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen10
def gen10D():
	N = random.randint(1, MAXN)
	K = random.randint(3, N - 1)
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen10
def gen10E():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = random.randint(3, N - 1)
	A = []
	for i in range(N):
		A.append(random.randint(MINA, MAXA))
	
	return [N, K, A]

@gen10
def gen10F():
	N = random.randint(int(.95 * MAXN), MAXN)
	K = 2
	A = []
	for i in range(N):
		A.append(random.randint(-2, 2))
	
	return [N, K, A]

###################################################################

def main():
	random.seed(20210829 ** 2142)
	test_format = str(GENDIR.resolve() / 'manual' / '{subtask}-{testid:0>2}.{ext}')

	gen = TestGenerator()
	gen.config(debug=False, test_format=test_format)
	

	gen.newTest("sample", 1, gen0A)
	gen.newTest("sample", 1, gen0B)
	gen.newTest("sample", 1, gen0C)
	gen.newTest("sample", 1, gen0D)
	# gen.newTest(0, 10, gen0D)
	
	gen.newTest("sub1", 2, gen1A)
	gen.newTest("sub1", 3, gen1B)
	gen.newTest("sub1", 2, gen1C)
	
	gen.newTest("sub2", 2, gen2A)
	gen.newTest("sub2", 3, gen2B)
	
	gen.newTest("sub3", 2, gen3A)
	gen.newTest("sub3", 3, gen3B)
	
	gen.newTest("sub4", 1, gen4A)
	gen.newTest("sub4", 1, gen4B)
	gen.newTest("sub4", 1, gen4C)
	gen.newTest("sub4", 1, gen4D)
	gen.newTest("sub4", 1, gen4E)
	
	gen.newTest("sub5", 2, gen5A)
	gen.newTest("sub5", 3, gen5B)
	
	gen.newTest("sub6", 1, gen6A)
	gen.newTest("sub6", 1, gen6B)
	gen.newTest("sub6", 3, gen6C)
	gen.newTest("sub6", 2, gen6D)
	gen.newTest("sub6", 3, gen6E)
	
	gen.newTest("sub7", 1, gen7A)
	gen.newTest("sub7", 1, gen7B)
	gen.newTest("sub7", 3, gen7C)
	
	gen.newTest("sub8", 1, gen8A)
	gen.newTest("sub8", 1, gen8B)
	gen.newTest("sub8", 3, gen8C)
	gen.newTest("sub8", 2, gen8D)
	
	gen.newTest("sub9", 2, gen9A)
	gen.newTest("sub9", 3, gen9B)
	
	gen.newTest("all", 1, gen10A)
	gen.newTest("all", 1, gen10B)
	gen.newTest("all", 1, gen10C)
	gen.newTest("all", 2, gen10D)
	gen.newTest("all", 3, gen10E)
	gen.newTest("all", 2, gen10F)
	
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
	genStart(main)
