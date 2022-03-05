SECTION .data
array:  dd 1,2,5,6,3,4
len:	equ $-array
Max:	db '0',10
SECTION .text
global _start
_start:
	mov 	ebx,0			; initial
	mov 	eax,[ebx + array]	
	mov 	ecx,eax
	mov	edx,len			; record the len to count
A1:
	mov 	eax,[ebx + array]	; traversal the array
	cmp 	eax,ecx
	jg  	A3			
	jmp 	A4
A2:
	add	[Max],ecx		; output and finish
	mov 	edx,2
	mov	ecx,Max
	mov	ebx,1
	mov	eax,4
	int	0x80

	mov	ebx,0
	mov	eax,1
	int	0x80

A3:
	mov 	ecx,eax			; updata the Max
	jmp 	A4		

A4:
	add 	ebx,4			; judge if finished
	cmp 	ebx,edx
	je	A2
	jmp	A1
	

	 
