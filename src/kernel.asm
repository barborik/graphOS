global _small_code_
extern _kernel_

segment _TEXT use16 class=CODE                          ; code segment (16bit code)
_small_code_:
..start:                                                ; .. denotes the label to be used as the entry point
    mov ax, 0x7e0                                       ; offset segments
    mov ds, ax
    mov ss, ax

    call _kernel_
    jmp $

segment _STACK STACK class=STACK                        ; stack segment
resb 8 * 1024
