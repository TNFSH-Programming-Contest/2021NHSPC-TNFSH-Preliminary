import random

def genRandomize(Q, krange=(-10000, 10000), qxweight=(1, 1, 1), opweight=(1, 1)):
	acf, bcf = [0, 1, 1], [0, 0, 0]
	
	Qs = []
	for qi in range(Q):
		rqi = random.choices([0, 1, 2], weights=qxweight)[0]
		if rqi == 0:
			k = random.randint(*krange)
			Qs.append([1, k])
		
		elif rqi == 1:
			op = random.choices('+*', weights=opweight)[0]
			i = random.choice([1, 2])
			
			if op == '+':
				ymin = max(-100, -10**8 - bcf[i])
				ymax = min(+100, +10**8 - bcf[i])
				y = random.randint(ymin, ymax)
				
				bcf[i] += y
			
			elif op == '*':
				mmax = min(10**4 // (abs(acf[i])+1), 10**8 // (abs(bcf[i])+1), 100)
				y = random.randint(0, mmax) * random.choice([1, -1])
				
				acf[i] *= y
				bcf[i] *= y
			
			Qs.append([2, i, op, y])
		
		elif rqi == 2:
			Qs.append([3])
	
	return Qs

def genAlternate(Q, has3=True, krange=(-10000, 10000), opweight=(1, 1)):
	rlen = 3 if has3 else 2
	
	op_pool = ['+']*opweight[0] + ['*']*opweight[1]
	random.shuffle(op_pool)
	
	acf, bcf = [0, 1, 1], [0, 0, 0]
	
	Qs = []
	for qi in range(Q):
		rqi = qi % rlen
		if rqi == 0:
			k = random.randint(*krange)
			Qs.append([1, k])
		
		elif rqi == 1:
			q2ri = qi // rlen
			op = op_pool[q2ri % len(op_pool)]
			i = [1, 2][(q2ri // len(op_pool)) % 2]
			
			if op == '+':
				ymin = max(-100, -10**8 - bcf[i])
				ymax = min(+100, +10**8 - bcf[i])
				y = random.randint(ymin, ymax)
				
				bcf[i] += y
			
			elif op == '*':
				mmax = min(10**4 // (abs(acf[i])+1), 10**8 // (abs(bcf[i])+1), 3)
				y = random.randint(0, mmax) * random.choice([1, -1])
				
				acf[i] *= y
				bcf[i] *= y
			
			Qs.append([2, i, op, y])
		
		elif rqi == 2:
			Qs.append([3])
	
	return Qs