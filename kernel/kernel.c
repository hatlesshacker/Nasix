#include <kernel.h>
#include <keyboard/kb.h>
#include <display/screen.h>
#include <multiboot.h>

//FIXME:: LibFalcon already has these exact implementations, still
//        we have to implement these here anyhow. Fix This.
inline void outportb (unsigned short _port, unsigned char _data) {
    asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
unsigned char inportb (unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void kmain(multiboot_info_t *mboot_ptr) {
    multiboot_module_t *mod = mboot_ptr->mods_addr;
    uint32_t contig_strt = 0x100000;

    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");
    keyboard_install();
    cls();

    printk("CPU Vendor: %s\n", get_cpuvendor());
    if (mboot_ptr->mods_count <= 0) {
        printk("failed to load initrd.", 1);
    }

    printk("Determining amount of available RAM... \n");
    if ((mboot_ptr->flags & MULTIBOOT_INFO_MEMORY) == 0)
        printk("bootloader did not set memory flags.\n");
    printk("%lu KB conventional memory, %lu MB extended memory.\n",
           (mboot_ptr->mem_lower), (mboot_ptr->mem_upper)/1024);

    printk("%d usable pages.\n",
           (mboot_ptr->mem_upper - mboot_ptr->mem_lower) / 8);

    printk("%d modules are loaded.\n", mboot_ptr->mods_count);
    if (mboot_ptr->flags & MULTIBOOT_INFO_MODS) {
        for (int i = 0; i < mboot_ptr->mods_count; i++) {
            int j = 1;
            printk("** Module No. %d is loaded at 0x%x.\n", j, (mod[i]).mod_start);
            contig_strt += ((mod[i]).mod_end) - ((mod[i]).mod_start);
            j++;
        }
    } else {
        printk("bootloader did not set module flags.");
    }
    printk("Contiguous memory starts from 0x%x.\n", contig_strt);

    for (;;);
}
