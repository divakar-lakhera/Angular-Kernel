/*
	kernel-loader.c
	Written By: Divakar Lakhera
	Performs Kernel Initialization and starts bootstrapping process.
	Called by Bridge.s
	Assembler Params: -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
*/

#include "headers/angular-kernel.h"
#include "headers/multiboot.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))	// check if ith bit is set.

int kmain(unsigned long magic, unsigned long addr)
{	
	asm volatile("cli");
	// Setup Text Mode
	while(!isReady())
	trySetVGATextState(1);
	VGATextClearScreen();
	
	kprintf("Kernel is loading..\n");


	// Setup GDT,Interrupts
	gdtInit();
	idtUpdate();
	timer_install();
	asm volatile ("sti");

	//



	kprintf("Ready !\n");
	kprintf("--------------------------------------------------------------\n\n");
	kprintf("Wecome To Angular v0.1\n");
	kprintf("Hello World\n");
	kprintf("Les Goo !");
	for(;;);
	return 0xBADBAD;
}
