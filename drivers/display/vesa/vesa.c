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

#include <multiboot.h>
#include <kernel.h>
#include <display/vesa.h>

VbeInfoBlock* VIB = 0x2000;
ModeInfoBlock* MIB = 0x3000;

void vbe_init(multiboot_info_t *multiboot) {
    regs16_t regx;
    VIB->VbeSignature[0] = 'V';
    VIB->VbeSignature[1] = 'B';
    VIB->VbeSignature[2] = 'E';
    VIB->VbeSignature[3] = '2';
    VIB->VbeVersion = 0x0200;

    regx.ax = 0x4F00;
    regx.es = 0x0;
    regx.di = 0x2000;
    rmcall (0x10, &regx);
}

int get_vbe_modeinfo(uint16_t mode)
{
    regs16_t regx;
    
    regx.ax = 0x4F01;
    regx.cx = mode;
    regx.es = 0x0;
    regx.di = 0x3000;

    rmcall (0x10, &regx);

    printk("showing information of VBE mode 0x%x..\n", mode);
    printk("start of LFB: 0x%x\n", MIB -> physbase);
    printk("%d Bits Per pixel\n", (uint16_t)MIB->bpp);
}