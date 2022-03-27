%include "boot.inc"
org 0x7e00
[bits 16]
	

	mov	ax,0xb800
	mov	gs,ax
	mov	ah,0x03
	mov	ecx,bootloader_tag_end - bootloader_tag
	xor	ebx,ebx
	mov	esi,bootloader_tag
	
output_bootloader_tag:
	mov	al,[esi]
	mov	word[gs:bx],ax
	inc	esi
	add	ebx,2
	loop	output_bootloader_tag

; empty descriptor
	mov	dword 	[GDT_START_ADDRESS + 0X00],0X00
	MOV	DWORD 	[GDT_START_ADDRESS + 0X04],0X00

; data segment 4GB
	MOV	DWORD	[GDT_START_ADDRESS + 0X08],0X0000FFFF
	MOV	DWORD	[GDT_START_ADDRESS + 0X0C],0X00CF9200

; heap/stack segment
	MOV	DWORD	[GDT_START_ADDRESS + 0X10],0X00000000
	MOV	DWORD	[GDT_START_ADDRESS + 0X14],0X00409600

; video memory descriptor
	MOV	DWORD	[GDT_START_ADDRESS + 0X18],0X80007FFF
	MOV	DWORD	[GDT_START_ADDRESS + 0X1C],0X0040920B

; plain mod text segment
	MOV	DWORD	[GDT_START_ADDRESS + 0X20],0X0000FFFF
	MOV	DWORD	[GDT_START_ADDRESS + 0X24],0X00CF9800

	mov	word [pgdt],39
	lgdt	[pgdt]
	
	push	eax
	mov	eax,pgdt
	pop	eax
	
	in	al,0x92
	or 	al,0000_0010B
	out	0x92,al
	
	cli
	mov	eax,cr0
	or	eax,1
	mov	cr0,eax

	jmp	dword CODE_SELECTOR:protect_mode_begin

[bits 32]
protect_mode_begin:
	mov	eax, DATA_SELECTOR
	MOV	ds,eax
	mov	es,eax
	mov	eax,STACK_SELECTOR
	mov	ss,eax
	mov	eax,VIDEO_SELECTOR
	mov	gs,eax

	mov	ecx,600
	mov	ebx,0
	mov	ax,0
	
clear:
	mov	[gs:ebx],ax
	add	ebx,2
	loop	clear		

	xor 	eax,eax
	xor	ebx,ebx
	xor	ecx,ecx,
	xor	edx,edx
	mov	dh,2
	mov	dl,0
	mov	bh,1
	mov	bl,1
	mov	al,'0'
	mov	ah,0
pop_char:
	push	eax
	xor	eax,eax
	mov	al,dh
	imul	eax,160
	mov	ecx,eax
	xor	eax,eax
	mov	al,dl
	add	ecx,eax
	add	ecx,eax
	pop	eax
	
	mov	[gs:ecx],ax
	call 	delay
	call	judge
	add	dh,bh
	add	dl,bl
	cmp	al,'9'
	je	C1
C2:
	inc	al
	cmp	ah,0xff
	je	C3
C4:
	inc	ah
	jmp	pop_char
	
	jmp	exit

C3:
	mov	ah,0
	dec	ah
	jmp	C4

C1:
	mov	al,'0'
	dec	al
	jmp	C2


judge:
	cmp	dh,0
	je	B1
A1:	
	cmp	dh,24
	je	B2
A2:	
	cmp	dl,0
	je	B3
A3:
	cmp	dl,79
	je	B4
A4:
	ret
B1:
	mov	bh,1
	jmp	A1
B2:
	mov	bh,-1
	jmp	A2
B3:
	mov	bl,1
	jmp	A3
B4:
	mov	bl,-1
	jmp	A4


delay:
	push	ebx
	push	ecx
	mov	bx,40h
for1:	
	mov	cx,0ffffh
for2:
	loop	for2
	dec	bx
	jnz	for1
	pop	ecx
	pop	ebx
	ret	

exit:
	jmp $

pgdt	dw 0
	dd GDT_START_ADDRESS

bootloader_tag db 'run bootloader'
bootloader_tag_end:

