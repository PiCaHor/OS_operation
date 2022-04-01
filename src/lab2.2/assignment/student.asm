; If you meet compile error, try 'sudo apt install gcc-multilib g++-multilib' first

%include "head.include"
; you code here

your_if:
; put your implementation here
	push	eax
	push	ebx
	push	ecx
	mov	eax,[a1]
	cmp	eax,12
	jge	A1
	
	mov	ecx,2
	idiv	ecx
	inc	eax
	mov	[if_flag],eax
	jmp	exit

A1:
	cmp	eax,24
	jge	A2

	mov	ecx,24
	sub	ecx,eax
	imul	ecx,eax
	mov	[if_flag],ecx
	jmp	exit
	
A2:
	shl	eax,4
	mov	[if_flag],eax
exit:	
	pop	ecx
	pop	ebx
	pop	eax	
your_while:
; put your implementation here
	push	ebx
	push	ecx
	push	edx
	mov	ebx,[a2]
	sub	ebx,12
	mov	edx,[while_flag]
A4:
	cmp	ebx,0
	jl	A5
	call	my_random
	mov	[edx+ebx],eax
	dec	ebx
	jmp	A4
A5:
	add	ebx,12
	mov	[a2],ebx	
	pop	edx
	pop	ecx
	pop	ebx

%include "end.include"

your_function:
; put your implementation here
	push	ebx
	push	ecx
	xor 	ebx,ebx
	xor	ecx,ecx
	mov	ebx,[your_string]
	
cycle:
	mov	cl,[ebx]
	cmp	cx,0
	je	exit_1
	push	cx
	call	print_a_char
	pop	cx
	inc	ebx
	jmp	cycle

exit_1:
	pop	ecx
	pop	ebx
