org 0x7c00
[bits 16]
xor ax, ax 
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

mov sp, 0x7c00
mov ax, 0xb800
mov gs, ax


mov ah, 0x01 ;blue
mov al, 'H'
mov [gs:2 * 0], ax

mov al, 'e'
mov [gs:2 * 1], ax

mov al, 'l'
mov [gs:2 * 2], ax

mov al, 'l'
mov [gs:2 * 3], ax

mov al, 'o'
mov [gs:2 * 4], ax

mov al, ' '
mov [gs:2 * 5], ax

mov al, 'W'
mov [gs:2 * 6], ax

mov al, 'o'
mov [gs:2 * 7], ax

mov al, 'r'
mov [gs:2 * 8], ax

mov al, 'l'
mov [gs:2 * 9], ax

mov al, 'd'
mov [gs:2 * 10], ax

mov ah, 0x07 ;white
mov al, 'H'
mov [gs:2 * 80], ax

mov al, 'e'
mov [gs:2 * 81], ax

mov al, 'l'
mov [gs:2 * 82], ax

mov al, 'l'
mov [gs:2 * 83], ax

mov al, 'o'
mov [gs:2 * 84], ax

mov al, ' '
mov [gs:2 * 85], ax

mov al, 'W'
mov [gs:2 * 86], ax

mov al, 'o'
mov [gs:2 * 87], ax

mov al, 'r'
mov [gs:2 * 88], ax

mov al, 'l'
mov [gs:2 * 89], ax

mov al, 'd'
mov [gs:2 * 90], ax


jmp $ ; 死循环

times 510 - ($ - $$) db 0
db 0x55, 0xaa
