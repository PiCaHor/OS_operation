[bits 32]

global asm_hello_world
global asm_lidt
global asm_halt
global asm_unhandled_interrupt
global asm_out_port
global asm_in_port
global asm_time_interrupt_handler
global asm_enable_interrupt

extern c_time_interrupt_handler

ASM_UNHANDLED_INTERRUPT_INFO db 'Unhandled interrput happened, halt...'
			     db 0
ASM_IDTR DW 0
	 DD 0

asm_enable_interrupt:
    	sti
    	ret
    
asm_time_interrupt_handler:
    	pushad
    	nop
	mov al, 0x20
    	out 0x20, al
    	out 0xa0, al
    
    	call c_time_interrupt_handler

    	popad
    	iret
    	
asm_unhandled_interrupt:
	cli
	mov	esi,ASM_UNHANDLED_INTERRUPT_INFO
	xor 	ebx,ebx
	mov	ah,0x03
.output_information:
	cmp	byte[esi],0
	je	.end
	mov	al,byte[esi]
	mov	word[gs:bx], ax
	inc	esi
	add	ebx,2
	jmp	.output_information
.end:
	jmp	$

asm_hello_world:
    	push 	eax
    	xor 	eax, eax

    	mov 	ah, 0x03 ;青色
    	mov 	al, '2'
    	mov 	[gs:2 * 0], ax

    	mov 	al, '0'
    	mov 	[gs:2 * 1], ax

    	mov 	al, '3'
    	mov 	[gs:2 * 2], ax

    	mov 	al, '3'
    	mov 	[gs:2 * 3], ax

    	mov 	al, '7'
    	mov 	[gs:2 * 4], ax

    	mov 	al, '2'
    	mov 	[gs:2 * 5], ax

    	mov 	al, '2'
    	mov 	[gs:2 * 6], ax

    	mov 	al, '8'
    	mov 	[gs:2 * 7], ax

    	pop 	eax
    	ret

asm_lidt:
	push 	ebp
	mov	ebp,esp
	push	eax
	
	mov	eax, [ebp + 4 * 3]
	mov	[ASM_IDTR],ax
	mov	eax,[ebp + 4 * 2]
	mov	[ASM_IDTR + 2],eax
	lidt	[ASM_IDTR]

	pop	eax
	pop	ebp
	ret

asm_out_port:
	push	ebp
	mov	ebp,esp
	
	push	edx
	push	eax
	mov	edx,[ebp + 4 * 2]
	mov	eax,[ebp + 4 * 3]
	out	dx,al
	
	pop	eax
	pop	edx
	pop	ebp
	ret


asm_in_port:
    	push ebp
    	mov ebp, esp

    	push edx
    	push eax
    	push ebx

    	xor eax, eax
   	mov edx, [ebp + 4 * 2] ; port
    	mov ebx, [ebp + 4 * 3] ; *value

    	in al, dx
    	mov [ebx], al

    	pop ebx
    	pop eax
    	pop edx
    	pop ebp
    	ret

asm_halt:
	jmp	$
