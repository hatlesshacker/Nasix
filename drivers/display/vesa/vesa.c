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
#include <stdint.h>
#include <display/screen.h>
#include <display/vesa.h>

#define RGB16(r, g, b) ((b & 31) | ((g & 63) << 5 | ((r & 31) << 11)))

void init_vesa_struct() {
    regs16_t *regx = 0x4000;
    VbeInfoBlock *VIB = 0x2000;
    ModeInfoBlock *MIB = 0x3000;
}
VbeInfoBlock *get_vbeiblock() {
    VbeInfoBlock *ret;
    ret = 0x2000;
    return ret;
}
ModeInfoBlock *get_miblock() {
    ModeInfoBlock *ret;
    ret = 0x3000;
    return ret;
}
regs16_t *get_vesareg() {
    regs16_t *ret;
    ret = 0x4000;
    return ret;
}

int init_vesa() {
    get_vbeiblock()->VbeSignature[0] = 'V';
    get_vbeiblock()->VbeSignature[1] = 'B';
    get_vbeiblock()->VbeSignature[2] = 'E';
    get_vbeiblock()->VbeSignature[3] = '2';
    get_vbeiblock()->VbeVersion = 0x0200;

    get_vesareg()->ax = 0x4F00;
    get_vesareg()->es = 0x0;
    get_vesareg()->di = 0x2000;
    int32_call(0x10, *get_vesareg());
}

int get_vbe_modeinfo(uint16_t mode) {
    if (mode < 0x100)
        return 0;
    get_vesareg()->ax = 0x4F01;
    get_vesareg()->cx = mode;
    get_vesareg()->es = 0x0;
    get_vesareg()->di = 0x3000;
    int32_call(0x10, *get_vesareg());

    printk("Info for VBE mode %x:\n", mode);
    printk("Start of Linear frame Buffer: %x\n", get_miblock()->physbase);
    printk("%d Bits per pixel.\n", get_miblock()->bpp);
    printk("Screen resolution: %dx%d", get_miblock()->Xres, get_miblock()->Yres);
}

void set_vbe_mode(uint16_t mode) {
    get_vesareg()->ax = 0x4F02;
    get_vesareg()->bx = mode;
    int32_call(0x10, *get_vesareg());
}