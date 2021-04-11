
all:run

boot.bin: sector1/boot.asm
	nasm $^ -f bin -o $@

extended_boot.o: sector2/extended_boot.asm
	nasm $^ -f elf64 -o $@

kernel.o: kernel/kernel.cpp
	x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c $^ -o $@

kernel.bin: linker.ld extended_boot.o kernel.o
	ld -T $<

os-image.bin: boot.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-x86_64 -fda $^
clean:
	rm *.o *.flp *.bin
