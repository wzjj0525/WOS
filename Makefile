all:Image

%.o:%.c
	x86_64-elf-gcc -m32 -Iinclude -ffreestanding -c -o $@ $<
%.o:%.asm
	nasm -f elf -o $@ $<

Image:boot/bootsect.bin kernel/kernel.bin
	cat $^ > $@

boot/bootsect.bin:boot/boot_sect_main.asm
	nasm -f bin -o boot/bootsect.bin boot/boot_sect_main.asm	
kernel/kernel.bin:kernel/to_main.o kernel/kernel.o driver/screen.o driver/ports.o kernel/util.o cpu/idt.o \
cpu/isr.o cpu/interrupt.o
	x86_64-elf-ld  -m elf_i386 --oformat binary -Ttext 0x1000 -o $@ $^


kernel/to_main.o:kernel/to_main.asm




run:
	bochs -q -f bochs/bochsrc.txt
clean:
	rm -f *.o *.bin boot/*.o kernel/*.o kernel/*.bin boot/bootsect.bin driver/*.o cpu/*.o

