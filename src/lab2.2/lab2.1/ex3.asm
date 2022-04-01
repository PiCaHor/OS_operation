org 	0x7c00
[bits 16]
xor	ax,ax
mov 	ds,ax
mov	ss,ax
mov	es,ax
mov	fs,ax
mov	gs,ax

mov	sp,0x7c00

mov 	ah,0x03
mov	bh,0
int	0x10

mov	ah,0x02
add	dh,5
add	dl,5
int	0x10

jmp	$

times	510-($-$$) db 0
db	0x55,0xaa
