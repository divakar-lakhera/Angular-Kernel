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

#include "string.h"
#include "stdio.h"
#include "time.h"
#include "arch.h"

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#endif

