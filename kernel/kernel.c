/*

This file if part of Nasix.

Copyright (c) 2020, Syed Nasim
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <kernel.h>
#include <keyboard/kb.h>
#include <display/screen.h>
#include <multiboot.h>
#include <timer.h>

void kmain(multiboot_info_t *mboot_ptr) {
    multiboot_module_t *mod = mboot_ptr->mods_addr;
    uint32_t contig_strt = 0x100000;

    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    timer_init();
    __asm__ __volatile__ ("sti");
    keyboard_install();
    cls();

    printk("CPU Vendor: %s\n", get_cpuvendor());
    if (mboot_ptr->mods_count <= 0) {
        printk("failed to load initrd.", 1);
    }

#define MULTIBOOT_INFO_MEMORY 0x00000001
#define MULTIBOOT_INFO_MODS   0x00000008

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
