org 0x7c00
[bits 16]

	mov 	ah,15
	int 	0x10
	mov 	ah,0
	int 	0x10

	mov	ah,02h
	mov	bh,0
	mov	dh,2
	mov	dl,0
	int	0x10

	mov	ch,1
	mov	cl,1	
	mov	bl,0
	mov	al,'0'
A1:
	push	cx
	mov	cx,1
	mov	ah,09h
	call 	delay
	int	0x10
	pop	cx
	call	change
	mov	ah,02h
	int	0x10	
	jmp	A1
	
change:
	cmp	al,'9'
	je	A2
A3:
	inc	al
	cmp	bl,0xff
	je	A4
	inc	bl
A5:
	add	dh,ch
	add	dl,cl
	call	judge
	ret
A4:	
	mov	bl,0
	dec	bl
	jmp	A5
A2:
	mov	al,'0'
	dec	al
	jmp	A3
judge:
	cmp	dh,25
	je	B1
	cmp	dh,-1
	je	B2
	cmp	dl,80
	je	B3	
	cmp	dl,-1
	je	B4
	ret
B1:	
	mov	dh,23
	mov	ch,-1
	jmp	judge

B2:
	mov	dh,1
	mov	ch,1
	jmp	judge

B3:	
	mov	dl,78
	mov	cl,-1
	jmp	judge
B4:
	mov	dl,1
	mov	cl,1
	jmp	judge

delay:
	push	bx
	push	cx
	mov	bx,40h
for1:
	mov	cx,0ffffh
for2:
	loop	for2
	dec	bx
	jnz	for1
	pop	cx
	pop	bx		
	ret

	jmp	$
	times 510-($-$$) db 0
	dw 0xAA55
