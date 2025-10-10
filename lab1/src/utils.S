.globl put32
put32:
	str w1,[x0]  //Store w1 to x0 (x0 指向的 mem address)
	ret // return

.globl get32
get32:
	ldr w0,[x0] // load x0 (x0 指向的 mem address) to w0
	ret

.globl delay
delay:
	subs x0, x0, #1
	bne delay // branch not zero
	ret