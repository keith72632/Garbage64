
all:run

boot.bin: sector1/boot.asm
	nasm $^ -f bin -o $@

extended_boot.bin: sector2/extended_boot.asm
	nasm $^ -f bin -o $@

boot.flp: boot.bin extended_boot.bin
	cat $^ > $@

run: boot.flp
	qemu-system-x86_64 -fda $^
clean:
	rm *.o *.flp *.bin
