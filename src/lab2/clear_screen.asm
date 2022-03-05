org 0x7c00
SECTION	.text
global	_start
_start:  
	mov ah,15
	int 0x10
	mov ah,0
	int 0x10

jmp $

times 510 - ($-$$) db 0
db 0x55, 0xaa
