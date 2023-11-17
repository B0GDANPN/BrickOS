#preparations
rm -f -r ../build
mkdir ../build
cd ../build

#loading boot.asm
nasm -fbin ../src/boot.asm -o boot.bin
dd if=/dev/zero of=boot.img bs=1024 count=1440
dd if=boot.bin of=boot.img conv=notrunc

nasm -felf32 ../src/tramplines.asm -o tramplines.o
nasm -felf32 ../src/pic/pic.asm -o pic.o

gcc -m32 -ffreestanding -c -o kernel.o ../src/kernel.c
gcc -m32 -ffreestanding -c -o print.o ../src/print/print.c
gcc -m32 -ffreestanding -c -o print_logo.o ../src/print/print_logo.c
gcc -m32 -ffreestanding -c -o utils.o ../src/utils/utils.c
gcc -m32 -ffreestanding -c -o alloc.o ../src/alloc/alloc.c
gcc -m32 -ffreestanding -c -o idt.o ../src/idt/idt.c
gcc -m32 -ffreestanding -c -o tramplins.o ../src/tramplins/tramplins.c
ld -m i386pe -o kernel.tmp -Ttext 0x20200 kernel.o print.o print_logo.o utils.o alloc.o idt.o tramplines.o tramplins.o pic.o

objcopy -I pe-i386 -O binary kernel.tmp kernel.bin
dd if=kernel.bin of=boot.img conv=notrunc seek=1
