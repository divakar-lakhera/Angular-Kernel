/*
	kernel-loader.c
	Written By: Divakar Lakhera
	Performs Kernel Initialization and starts bootstrapping process.
	Called by Bridge.s
	Assembler Params: -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
*/

#include "headers/angular-kernel.h"
#include "headers/multiboot.h"

int kmain(unsigned long magic, unsigned long addr)
{	
	while(!isReady())
	trySetVGATextState(1);
	VGATextClearScreen();
	// Start loading multiboot information structure
	multiboot_info_t *multibootBlock;
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC){
    	kprintf("Invalid magic number: 0x%x\n", (unsigned) magic);
    	return;
    }
	kprintf("Video Driver Loaded Successfully..\n");
	kprintf("Wecome To Angular v0.1\n");
	kprintf("Hello World\n");
	kprintf("Les Goo !");
	return 0xBADBAD;
}
