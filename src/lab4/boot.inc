; ____________Loader______________

LOADER_SECTOR_COUNT equ 5

LOADER_START_SECTOR equ 1

LOADER_START_ADDRESS equ 0x7e00

; ___________GDT______________

GDT_START_ADDRESS equ 0x8800
; __________Selector____________________
DATA_SELECTOR 	equ 0x8
STACK_SELECTOR	equ 0x10
VIDEO_SELECTOR	equ 0x18
VIDEO_NUM equ 0x18
CODE_SELECTOR	equ 0x20
