.globl memzero
memzero:
	str xzr, [x9], #8
	subs x10, x10, #8
	b.gt memzero
	ret