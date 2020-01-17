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
#include <display/screen.h>
#include <kernel/x86.h>
#include <keyboard/kb.h>

unsigned char scanCodeToAsciiTable[] = {
    0, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE, TAB,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', ENTER, 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, KF1, KF2, KF3, KF4, KF5,
    KF6, KF7, KF8, KF9, KF10, 0, 0, KHOME, KUP, KPGUP, '-', KLEFT, 0, KRIGHT, '+', KEND,
    KDOWN, KPGDN, KINS, KDEL, 0, 0, 0, KF11, KF12
};

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r) {
    unsigned char scn = inportb(0x60);
    if (scn & 0x80) {
        return;
    } else {

        kputch(scanCodeToAsciiTable[scn]);
    }
}
unsigned char kgetc() {
    //TODO
}

void turn_on_leds() {
    outportb(0x60, SET_LED);
    outportb(0x60, 0x07);
    return;
}

void turn_off_leds() {
    outportb(0x60, SET_LED);
    outportb(0x60, 0x00);
    return;
}

void turn_on_capsLock() {
    outportb(0x60, SET_LED);
    outportb(0x60, 0x04);
    return;
}

void turn_on_numLock() {
    outportb(0x60, SET_LED);
    outportb(0x60, 0x02);
    return;
}

void turn_on_scrollLock() {
    outportb(0x60, SET_LED);
    outportb(0x60, 0x01);
    return;
}
/* Installs the keyboard handler into IRQ1 */
void keyboard_install() {
    irq_install_handler(1, keyboard_handler);
}
