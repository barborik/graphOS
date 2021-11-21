[org 0x7c00]                                ; origin of local addressing, BIOS loads the bootloader code here

mov [BOOT_DISK], dl                         ; dl stores the disk number right after boot

xor ax, ax
mov es, ax

mov ah, 0				                    ; set video mode
mov al, 3				                    ; 80x25 16 color text (CGA,EGA,MCGA,VGA)
int 0x10

mov ah, 2				                    ; read disk sectors
mov al, 128				                    ; number of sectors to read (1-128 decimal)
mov ch, 0				                    ; track/cylinder number (0-1023 decimal)
mov cl, 2				                    ; sector number | 1 = boot sector, 2->n = kernel
mov dh, 0				                    ; head number (0-15 decimal)
mov dl, [BOOT_DISK]			                ; drive number | 0 = A:
mov bx, KERNEL_ORIGIN                       ; es:bx = pointer to buffer (where to load)
int 0x13

jmp KERNEL_ORIGIN

BOOT_DISK:	        db	    0
KERNEL_ORIGIN:      equ     0x7e00

times 510 - ( $ - $$ ) db 0		            ; MBR padding
db 0x55, 0xaa				                ; make bootable