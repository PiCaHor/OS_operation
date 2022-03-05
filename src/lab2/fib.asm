section .data
array	times 20 dd 0 
len	equ $-array

section .text
global _start
_start:
	mov	eax,1			; initial
	mov	ebx,1
	mov	ecx,0
	mov	edx,array
	mov	[ecx + array],eax	; calculate the first and the second
	add	ecx,4
	mov	[ecx + array],ebx
	add	ecx,4
	jmp	A1		
A1:	
	cmp	ecx,len			; judge if finish
	je	A4
	mov	edx,eax			; calculate the new one
	add	edx,ebx			
	mov	[ecx + array],edx
	add	ecx,4
	mov	eax,ebx			; update for next calculation
	mov	ebx,edx
	jmp	A1

A4:
	mov	ebx,0			; finish
	mov	eax,1
	int	0x80
