all: Image
aa
Image: tools/build boot/bootsect boot/setup
	tools/build boot/bootsect boot/setup > Image

tools/build: tools/build.c
	gcc -o tools/build tools/build.c
	
boot/bootsect: boot/bootsect.s 
	as86 -0 -a -o boot/bootsect.o boot/bootsect.s
	ld86 -0 -s -o boot/bootsect boot/bootsect.o

boot/setup: boot/setup.s
	as86 -0 -a -o boot/setup.o boot/setup.s
	ld86 -0 -s -o boot/setup boot/setup.o
clean:
	rm -f boot/bootsect.o
	rm -f boot/bootsect
	rm -f boot/setup.o
	rm -f boot/setup
	rm -f tools/build
	rm -f tools/build.o
	rm -f Image
