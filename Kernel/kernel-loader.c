/*
	kernel-loader.c
	Written By: Divakar Lakhera
	Performs Kernel Initialization and starts bootstrapping process.
	Called by Bridge.s
	Assembler Params: -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
*/

#include "headers/angular-kernel.h"

int main()
{	
	while(!isReady())
		trySetVGATextState(1);
	VGATextClearScreen();
	kprintf("Video Driver Loaded Successfully..\n");
	kprintf("Wecome To Angular v0.1\n");
	kprintf("Hello World");
	return 0xBADBAD;
}
