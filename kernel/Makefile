


all: run

kernel.bin: kernel_entry.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o:kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

bootsect.dis: bootsect.asm
	nasm $< -f bin -o $@

run: os-image.bin
	qemu-system-i386 -fda $<

clean:
	rm *.bin *.o *.dis
