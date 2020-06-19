/*
	Angular Kernel 
	Written By : Divakar Lakhera
	Licensed Under: GNU GPL 3 (Read LICENSE for more info)

	angular-kernel.h
	Contains all the basic utilites and definations for working of kernel.
*/

#ifndef __angular__base____
#define __angular__base____

typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;
typedef int size_t;
void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);
void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *dest, char val, size_t count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
void *itoa (char *buf, int base, int d);
#endif

