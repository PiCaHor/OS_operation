org 0x7c00
[bits 16]
xor     ax,ax

mov     ds,ax   ; initial the segment register
mov     ss,ax
mov     es,ax
mov     fs,ax
mov     gs,ax

mov     sp,0x7c00       ; set the stack pointer
mov     ax,0xb800       ; set the segment register
mov     gs,ax

mov     ah,0x70         ; set color  

mov     al,'2'
mov     [gs:2 * (12*80+12)],ax

mov     al,'0'
mov     [gs:2 * (12*80+13)],ax

mov     al,'3'
mov     [gs:2 * (12*80+14)],ax

mov     al,'3'
mov     [gs:2 * (12*80+15)],ax

mov     al,'7'
mov     [gs:2 * (12*80+16)],ax

mov     al,'2'
mov     [gs:2 * (12*80+17)],ax

mov     al,'2'
mov     [gs:2 * (12*80+18)],ax

mov     al,'8'
mov     [gs:2 * (12*80+19)],ax

jmp 	$ 

times 	510 - ($ - $$) db 0
db 	0x55, 0xaa
