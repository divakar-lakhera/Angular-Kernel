#ifndef KERNEL_STDIO__
#define KERNEL_STDIO__
#include "angular-kernel.h"

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);
void VGATextSetColor(u8int fg, u8int bg);
void VGATextClearScreen();
void VGATextPutch(char ch);
u8int trySetVGATextState(u8int state);
void kprintf (const char *format, ...);

#endif