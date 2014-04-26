all: kernel

entry.o: entry.asm
	nasm -f elf32 entry.asm -o entry.o

kernel.o: kernel.c *.h
	gcc -std=c99 -m32 -c kernel.c -o kernel.o

main.o: main.c *.h
	gcc -std=c99 -m32 -c main.c -o main.o

kernel: entry.o kernel.o main.o
	ld -m elf_i386 -T link.ld -o kernel entry.o kernel.o main.o

clean:
	rm -rf *.o kernel
