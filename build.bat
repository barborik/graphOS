nasm -f obj src\boot.asm -o bin\boot.o
owcc -c -bdos -fno-stack-check -Os -s -march=i86 -o bin\kernel.o src\kernel.c bin\boot.o

wlink form raw bin file bin\boot.o, bin\kernel.o name bin\graphOS.bin OPTION MAP=kernel.map

type zeros >> bin\graphOS.bin
