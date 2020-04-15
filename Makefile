#
#
# Makefile for Nasix Kernel.
# Assuming Libfalcon is installed under /usr/.
#


FALCON = /usr/
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -w -I./include/ -I$(FALCON)/include/libfalcon/
AS = nasm
ASF = -f elf
LINKER = ld 
LINKERFLAGS = -m elf_i386 -T scripts/link.ld
EMU = qemu-system-i386

OBJS =

include lib/makefile
include kernel/makefile
include drivers/makefile
include boot/makefile

## **** The kernel bootable image ****
kernel.iso : kernel.bin scripts/grub.cfg
	echo "** Creating Bootable Image.."
	mkdir -p isodir
	mkdir -p isodir/boot
	cp kernel.bin isodir/boot/kernel.bin
	cp initrd/initrd.sys isodir/initrd.sys
	mkdir -p isodir/boot/grub
	cp scripts/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso isodir
	echo "** Build Successfull."

kernel.bin: scripts/link.ld $(OBJS)
	echo "** Linking Stuffs Together.." #ASSUMING LIBFALCON IS INSTALLED IN /USR/LIB/
	$(LINKER) $(LINKERFLAGS) -o kernel.bin $(OBJS) -L$(FALCON)/lib/ -lfalcon

%.o: %.c
	@echo "  CC       $@"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	@echo "  NASM     $@"
	@$(AS) $(ASF) $< -o $@

clean:
	rm -rf isodir $(OBJS) *.bin *.iso

test: kernel.iso
	echo "** Testing Nasix with qemu."
	$(EMU) -cdrom kernel.iso
