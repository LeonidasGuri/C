#!/usr/bin/env python
import string
import random

def id_generator(size=15, chars=string.ascii_uppercase + string.digits):
	return ''.join(random.choice(chars) for x in range(size))

def day_generator():
	return random.randrange(1,8)

def prod_generator():
	return 'P%d' % random.randrange(1,200)

def prod_list_generator():
	l = []
	for i in range(random.randrange(0, 10)):
		l.append('%s,%d;' % (prod_generator(), random.randrange(1,10)))
	return ''.join(l)

N = 100
P = []
for i in range(N):
	P.append(id_generator())
M = 500
for i in range(M):
	print day_generator(), random.choice(P), prod_list_generator()
