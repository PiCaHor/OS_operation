org	0x7c00
[bits	16]

	mov	ah,0x02
	mov	dh,12
	mov	dl,12
	mov	bh,0
	int	0x10

	mov	ah,0x09
	mov	bh,0
	mov	bl,0x0a
	mov	cx,1

	mov	al,'2'
	call	A1

	mov	al,'0'
	call	A1

	mov	al,'3'
	call	A1

	mov	al,'3'
	call	A1

	mov	al,'7'
	call	A1

	mov	al,'2'
	call	A1

	mov	al,'2'
	call	A1

	mov	al,'8'
	call	A1
	jmp	A2
A1:
	mov	ah,0x09
	int	0x10
	add	dl,1
	mov	ah,0x02
	int	0x10
	ret

A2:
	jmp	$

	times	510-($-$$) db 0
	db	0x55,0xaa


