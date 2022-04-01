%include "boot.inc"
org 0x7c00
[bits 16]
	
	xor	ax,ax
	mov	ds,ax
	mov	ss,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax

	mov	sp,0x7c00
	mov	bx,0x7e00
load_bootloader:
	mov	ah,0x02
	mov	al,5
	mov	ch,0x00
	mov	dh,0x00
	mov	dl,80h
	mov	cl,0x02
	int	0x13
.wait:
	jc	.wait

	jmp	0x0000:0x7e00
	jmp	$

	times	510-($-$$) db 0
	db 	0x55,0xaa	
	
		






	
