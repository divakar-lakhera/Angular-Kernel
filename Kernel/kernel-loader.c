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
	while(!isReady())
	trySetVGATextState(1);
	VGATextClearScreen();
	kprintf("Kernel is loading..\n");
	// Start loading multiboot information structure
	multiboot_info_t *multibootBlock;
	multiboot_info_t *AddressBlock;
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC){
    	kprintf("Invalid magic number: 0x%x\n", (unsigned) magic);
    	return;
    }
	AddressBlock = (multiboot_info_t *) addr;

	/* Print out the flags. */
	kprintf ("flags = 0x%x\n", (unsigned) AddressBlock->flags);

	/* Are mem_* valid? */
	if (CHECK_FLAG (AddressBlock->flags, 0))
		kprintf ("mem_lower = %uKB, mem_upper = %uKB\n",
				(unsigned) AddressBlock->mem_lower, (unsigned) AddressBlock->mem_upper);

	/* Is boot_device valid? */
	if (CHECK_FLAG (AddressBlock->flags, 1))
		kprintf ("boot_device = 0x%x\n", (unsigned) AddressBlock->boot_device);
	
	/* Is the command line passed? */
	if (CHECK_FLAG (AddressBlock->flags, 2))
		kprintf ("cmdline = %s\n", (char *) AddressBlock->cmdline);

	/* Are mods_* valid? */
	if (CHECK_FLAG (AddressBlock->flags, 3))
		{
		multiboot_module_t *mod;
		int i;
		
		kprintf ("mods_count = %d, mods_addr = 0x%x\n",
				(int) AddressBlock->mods_count, (int) AddressBlock->mods_addr);
		for (i = 0, mod = (multiboot_module_t *) AddressBlock->mods_addr;
			i < AddressBlock->mods_count;
			i++, mod++)
			kprintf (" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
					(unsigned) mod->mod_start,
					(unsigned) mod->mod_end,
					(char *) mod->cmdline);
		}

	/* Bits 4 and 5 are mutually exclusive! */
	if (CHECK_FLAG (AddressBlock->flags, 4) && CHECK_FLAG (AddressBlock->flags, 5))
		{
		kprintf ("Both bits 4 and 5 are set.\n");
		return;
		}

	/* Is the symbol table of a.out valid? */
	if (CHECK_FLAG (AddressBlock->flags, 4))
		{
		multiboot_aout_symbol_table_t *multiboot_aout_sym = &(AddressBlock->u.aout_sym);
		
		kprintf ("multiboot_aout_symbol_table: tabsize = 0x%0x, "
				"strsize = 0x%x, addr = 0x%x\n",
				(unsigned) multiboot_aout_sym->tabsize,
				(unsigned) multiboot_aout_sym->strsize,
				(unsigned) multiboot_aout_sym->addr);
		}

	/* Is the section header table of ELF valid? */
	if (CHECK_FLAG (AddressBlock->flags, 5))
		{
		multiboot_elf_section_header_table_t *multiboot_elf_sec = &(AddressBlock->u.elf_sec);

		kprintf ("multiboot_elf_sec: num = %u, size = 0x%x,"
				" addr = 0x%x, shndx = 0x%x\n",
				(unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size,
				(unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
		}

	/* Are mmap_* valid? */
	if (CHECK_FLAG (AddressBlock->flags, 6))
		{
		multiboot_memory_map_t *mmap;
		
		kprintf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
				(unsigned) AddressBlock->mmap_addr, (unsigned) AddressBlock->mmap_length);
		for (mmap = (multiboot_memory_map_t *) AddressBlock->mmap_addr;
			(unsigned long) mmap < AddressBlock->mmap_addr + AddressBlock->mmap_length;
			mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
										+ mmap->size + sizeof (mmap->size)))
			kprintf (" size = 0x%x, base_addr = 0x%x%08x,"
					" length = 0x%x%08x, type = 0x%x\n",
					(unsigned) mmap->size,
					(unsigned) (mmap->addr >> 32),
					(unsigned) (mmap->addr & 0xffffffff),
					(unsigned) (mmap->len >> 32),
					(unsigned) (mmap->len & 0xffffffff),
					(unsigned) mmap->type);
		}
	kprintf("Ready !\n");
	kprintf("--------------------------------------------------------------\n\n");
	kprintf("Wecome To Angular v0.1\n");
	kprintf("Hello World\n");
	kprintf("Les Goo !");
	return 0xBADBAD;
}
