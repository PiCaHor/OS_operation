org 0x7c00
[bits 16]

	xor	ax,ax
	mov	bh,0
	mov	dh,12
	mov	dl,12
	mov	ah,0x02
	int	0x10
        mov     bl,0x0a 
	mov	cx,1
	jmp	A1
A1:
	mov	ah,0
	int	0x16
	jmp	A2

A2:
	mov	ah,0x09
	int	0x10
	add	dl,1
	mov	ah,0x02
	int	0x10
	jmp	A1
	
	times 	510-($-$$) DB 0
	dw	0xAA55		
