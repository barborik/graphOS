nasm -f bin src/boot.asm -o bin/boot.bin

gcc -c -m32 src/kernel.c -o bin/kernel.o
objcopy -O binary -j .text bin/kernel.o bin/kernel.bin

rm bin/kernel.o

cat bin/boot.bin > bin/graphOS.bin
cat bin/kernel.bin >> bin/graphOS.bin
head -c 512 /dev/zero >> bin/graphOS.bin
