
CC=gcc
CFLAGS=-std=c99 -m32
DEPS=kernel.h io.h
OBJS=entry.o kernel.o main.o io.o screen.o simulation.o kb.o

all: kernel

entry.o: entry.asm
	nasm -f elf32 entry.asm -o entry.o

kernel.o: kernel.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main.o: main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

io.o: io.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

screen.o: screen.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simulation.o: simulation.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kb.o: kb.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kernel: $(OBJS)
	ld -m elf_i386 -T link.ld -o kernel $(OBJS)
	chmod +x kernel

clean:
	rm -rf *.o kernel
