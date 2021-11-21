nasm -f bin src\boot.asm -o bin\boot.bin

nasm -f obj src\kernel.asm -o bin\kernel.asm.o
owcc -c -bdos -fno-stack-check -Os -s -march=i86 -o bin\kernel.c.o src\kernel.c bin\kernel.asm.o

wlink form raw bin file bin\kernel.asm.o, bin\kernel.c.o name bin\kernel.bin OPTION MAP=kernel.map

type bin\boot.bin > bin\graphOS.bin
type bin\kernel.bin >> bin\graphOS.bin
type zeros >> bin\graphOS.bin
