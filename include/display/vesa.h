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

typedef struct vbe_control_info {
	char vbe_signature[4];
	unsigned short vbe_version;
	unsigned int vbe_oem_string_ptr;
	unsigned int vbe_capabilities;
	unsigned int vbe_video_mode_ptr;
	unsigned short vbe_total_memory;
	unsigned short vbe_oem_software_rev;
	unsigned int vbe_oem_vendor_name_ptr;
	unsigned int vbe_oem_product_name_ptr;
	unsigned int vbe_oem_product_rev_ptr;
	unsigned char vbe_reserved[222];
	char vbe_oem_data[256];
} __attribute__((packed)) vbe_control_info_t;

typedef struct vbe_mode_info {
	// Basic VBE
	unsigned short mode_attributes;
	unsigned char win_a_attributes;
	unsigned char win_b_attributes;
	unsigned short win_granularity;
	unsigned short win_size;
	unsigned short win_a_segment;
	unsigned short win_b_segment;
	unsigned int win_func_ptr;
	unsigned short bytes_per_scanline;

	// VBE 1.2+
	unsigned short x_resolution;
	unsigned short y_resolution;
	unsigned char x_char_size;
	unsigned char y_char_size;
	unsigned char number_of_planes;
	unsigned char bits_per_pixel;
	unsigned char number_of_banks;
	unsigned char memory_model;
	unsigned char bank_size;
	unsigned char number_of_image_panes;
	unsigned char reserved_vbe12;

	// Direct Color Modes
	unsigned char red_mask_size;
	unsigned char red_field_position;
	unsigned char green_mask_size;
	unsigned char green_field_position;
	unsigned char blue_mask_size;
	unsigned char blue_field_position;
	unsigned char rsvd_mask_size;
	unsigned char rsvd_field_position;
	unsigned char direct_color_mode_info;

	// VBE 2.0+
	unsigned int phys_base_ptr;
	unsigned int reserved_20_1;
	unsigned short reserved_20_2;

	// VBE 3.0+
	unsigned short lin_bytes_per_scanline;
	unsigned char bnk_number_of_image_pages;
	unsigned char lin_number_of_image_pages;
	unsigned char lin_red_mask_size;
	unsigned char lin_red_field_position;
	unsigned char lin_green_mask_size;
	unsigned char lin_green_field_position;
	unsigned char lin_blue_mask_size;
	unsigned char lin_blue_field_position;
	unsigned char lin_rsvd_mask_size;
	unsigned char lin_rsvd_field_position;
	unsigned int max_pixel_clock;

	unsigned char reserved[189];
} __attribute__((packed)) vbe_mode_info_t;

void vbe_init(multiboot_info_t* mboot);
void vbe_putpixel(unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b);
