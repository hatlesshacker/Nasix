#include <kernel.h>
#include <keyboard/kb.h>
#include <display/screen.h>

unsigned short getram();

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

void kmain() {
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");
    keyboard_install();
    cls();

    printk("CPU Vendor: %s\n", get_cpuvendor());

    for (;;);
}
