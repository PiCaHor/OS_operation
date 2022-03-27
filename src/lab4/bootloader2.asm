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

		
	mov	ecx,protect_mode_tag_end - protect_mode_tag
	mov	ebx, 80 * 2
	mov	esi, protect_mode_tag
	mov	ah,0x3

output_protect_mode_tag:
	mov	al,[esi]
	mov	word[gs:ebx],ax
	add	ebx,2
	inc	esi
	loop	output_protect_mode_tag

jmp $

pgdt	dw 0
	dd GDT_START_ADDRESS

bootloader_tag db 'run bootloader'
bootloader_tag_end:

protect_mode_tag db 'enter protect mode'
protect_mode_tag_end:
