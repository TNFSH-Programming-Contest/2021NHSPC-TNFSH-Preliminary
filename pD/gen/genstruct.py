import random

def randomInserted(v, w):
	totlen = len(v) + len(w)
	res = [None  for i in range(totlen)]
	for vi, resi in zip(range(len(v)), sorted(random.sample(range(totlen), len(v)))):
		res[resi] = v[vi]
	
	wi = 0
	for i in range(totlen):
		if res[i] == None:
			res[i] = w[wi]
			wi += 1
	
	return res

def randomSegments(N, v):
	vdif = sorted([0, N, *random.sample(range(1, N-1), len(v)-1)])
	
	res = []
	for i in range(len(v)):
		res.extend([v[i]]*(vdif[i+1] - vdif[i]))
	
	return res

def genHills(N, k, th=2/3, nsth=0, hlim=None, llim=None):
	hillcnt = int(N * th)
	vllycnt = N - hillcnt
	
	hill = max(k // int(N * th), 1)
	noise = int(k*nsth)
	
	if hlim == None:
		hlim = (max(hill-noise, 1), min(hill+noise, k))
	
	if llim == None:
		llim = (1, max((hill - noise) // vllycnt, 1))
	
	vhill = [random.randint(*hlim)  for i in range(hillcnt)]
	vvlly = [random.randint(*llim)  for i in range(vllycnt)]
	
	return randomInserted(vhill, vvlly)