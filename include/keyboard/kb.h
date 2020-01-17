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

void keyboard_install();
unsigned char kgetc();
void turn_on_leds(void);
void turn_off_leds(void);
void turn_on_capsLock(void);
void turn_on_numLock(void);
void turn_on_scrollLock(void);

#define SET_LED 0xED
#define ESC 27
#define BACKSPACE '\b'
#define TAB '\t'
#define ENTER '\n'

// Non-ASCII special scancodes // Esc in scancode is 1
#define KESC 1
#define KF1 0x3B
#define KF2 (KF1+1)
#define KF3 (KF2+1)
#define KF4 (KF3+1)
#define KF5 (KF4+1)
#define KF6 (KF5+1)
#define KF7 (KF6+1)
#define KF8 (KF7+1)
#define KF9 (KF8+1)
#define KF10 (KF9+1)
#define KF11 (KF10+1)
#define KF12 (KF11+1)
// When one of the above is pressed they will return this ascii
#define F1 200
#define F2 (F1+1)
#define F3 (F2+1)
#define F4 (F3+1)
#define F5 (F4+1)
#define F6 (F5+1)
#define F7 (F6+1)
#define F8 (F7+1)
#define F9 (F8+1)
#define F10 (F9+1)
#define F11 (F10+1)
#define F12 (F11+1)

// Cursor Keys
#define KINS 0x52
#define KDEL 0x53
#define KHOME 0x47
#define KEND 0x4F
#define KPGUP 0x49
#define KPGDN 0x51
#define KLEFT 0x4B
#define KUP 0x48
#define KDOWN 0x50
#define KRIGHT 0x4D
// When one of the above is pressed they will return this ascii
#define INS 220
#define DEL 221
#define HOME 222
#define END 223
#define PGUP 224
#define PGDN 225
#define LEFT 226
#define UP 227
#define DOWN 228
#define RIGHT 229

#define MAKE_SHIFT_L 0x2A
#define MAKE_SHIFT_R 0x36
#define BREAK_SHIFT_L 0xAA
#define BREAK_SHIFT_R 0xB6

#define MAKE_NUM_LOCK 0x45
#define MAKE_CAPS_LOCK 0x3A
#define MAKE_SCROLL_LOCK 0x46
#define BREAK_CAPS_LOCK 0xBA

