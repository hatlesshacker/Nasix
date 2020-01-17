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
#include <display/vesa.h>

static vbe_control_info_t *vbe_control;
static vbe_mode_info_t *vbe_mode;

static unsigned int* vbe_framebuffer;

void vbe_init(multiboot_info_t *multiboot) {
    vbe_control = (vbe_control_info_t *) multiboot->vbe_control_info;
    vbe_mode = (vbe_mode_info_t *) multiboot->vbe_mode_info;
    vbe_framebuffer = (unsigned int *) vbe_mode->phys_base_ptr;
}

void vbe_putpixel(unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b) {
    vbe_framebuffer[(vbe_mode->x_resolution * y) + x] = (r << 16 | g << 8 | b << 0 | 0xCC << 24);
}