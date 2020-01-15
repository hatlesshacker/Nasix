CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -w -I./include
AS = nasm
ASF = -f elf
LINKER = ld 
LINKERFLAGS = -m elf_i386 -T scripts/link.ld
EMU = qemu-system-i386

OBJS =

include lib/makefile
include kernel/makefile
include drivers/display/makefile
include drivers/keyboard/makefile
include boot/makefile

## **** The kernel bootable image ****
kernel.iso : kernel.bin scripts/grub.cfg
	echo "** Creating Bootable Image.."
	mkdir -p isodir
	mkdir -p isodir/boot
	cp kernel.bin isodir/boot/kernel.bin
	mkdir -p isodir/boot/grub
	cp scripts/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso isodir
	echo "** Build Successfull."

kernel.bin: scripts/link.ld $(OBJS)
	echo "** Linking Stuffs Together.."
	$(LINKER) $(LINKERFLAGS) -o kernel.bin $(OBJS) lib/libfalcon.a

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