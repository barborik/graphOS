global _small_code_
extern _kernel_

segment _TEXT use16 class=CODE              ; code segment (16bit code)
_small_code_:                               ; watcom linker needs this label
..start:                                    ; .. denotes the label to be used as the entry point

mov ax, BOOT_ORIGIN                         ; set segments so that we get the full 64KiB for code, data and stack experience
mov ds, ax
mov ss, ax
mov sp, stack_top

mov [BOOT_DISK], dl                         ; dl stores the disk number right after boot

mov ah, 0				                    ; set video mode
mov al, 3				                    ; 80x25 16 color text (CGA,EGA,MCGA,VGA)
int 0x10

mov ah, 2				                    ; read disk sectors
mov al, 128				                    ; number of sectors to read (1-128 decimal)
mov ch, 0				                    ; track/cylinder number (0-1023 decimal)
mov cl, 2				                    ; sector number | 1 = boot sector, 2->n = kernel
mov dh, 0				                    ; head number (0-15 decimal)
mov dl, [BOOT_DISK]			                ; drive number
mov bx, KERNEL_ORIGIN                       ; es:bx = pointer to buffer (where to load)
mov es, bx
xor bx, bx
int 0x13

jmp KERNEL_ORIGIN:0                         ; far jump to alter cs:ip

BOOT_DISK:	        db	    0
BOOT_ORIGIN:        equ     0x7c0
KERNEL_ORIGIN:      equ     0x7e0

times 510 - ( $ - $$ ) db 0		            ; MBR padding
db 0x55, 0xaa				                ; make bootable

call _kernel_                               ; hand over execution to the kernel
jmp $                                       ; fail safe

segment _STACK STACK class=STACK            ; stack segment 8KiB in size
resb 8 * 1024
stack_top:
