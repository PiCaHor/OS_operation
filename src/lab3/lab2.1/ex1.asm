org 0x7c00
[bits 16]
xor 	ax,ax

mov	ds,ax	; initial the segment register
mov	ss,ax
mov	es,ax
mov	fs,ax
mov	gs,ax

mov	sp,0x7c00	; set the stack pointer
mov	ax,0xb800	; set the segment register
mov	gs,ax

mov	ah,0x01		; set color blue 

mov	al,'H'
mov	[gs:2 * 0],ax

mov	al,'e'
mov	[gs:2 * 1],ax

mov	al,'l'
mov	[gs:2 * 2],ax

mov	al,'l'
mov	[gs:2 * 3],ax

mov	al,'o'
mov	[gs:2 * 4],ax

mov	al,' '
mov	[gs:2 * 5],ax

mov	al,'w'
mov	[gs:2 * 6],ax

mov	al,'o'
mov	[gs:2 * 7],ax

mov	al,'r'
mov	[gs:2 * 8],ax

mov	al,'l'
mov	[gs:2 * 9],ax

mov	al,'d'
mov	[gs:2 * 10],ax

jmp	$

times	510 - ($-$$) db 0
db	0x55,0xaa
