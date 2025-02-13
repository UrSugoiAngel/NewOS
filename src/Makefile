SOURCES=main.o boot.o portio.o screen.o idt.o gdt.o interrupt.o irq.o isr.o
CFLAGS=-ffreestanding -fno-stack-protector -Iinclude -Wall -Wextra -Wpedantic
LDFLAGS=-Tlink.ld
ASFLAGS=-f elf32

default: run

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	i686-elf-ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $< -o $@

.c.o:
	i686-elf-gcc $(CFLAGS) -c $< -o $@

iso: all
	mkdir -p iso/boot/grub
	cp kernel iso/boot/kernel
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o bin/kernel.iso iso

run: iso
	bochs -f bochsrc.txt