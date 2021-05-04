/*
    Intel x86 Global Discriptor Table (i32_GDT)
    Written By: Divakar Lakhera
    Angular Kernel
*/
#include "i32Gdt.h"

struct gdtEntry gdt[3];  // null,CS,DS
struct gdtPointer kernelGDT;

void setEntry(int segmentSelector,unsigned long baseAddress,unsigned long limitAddress,unsigned char accessBit,unsigned char granularity) {
    gdt[segmentSelector].base_low = (baseAddress & 0xFFFF);
    gdt[segmentSelector].base_middle = (baseAddress >> 16) & 0xFF;
    gdt[segmentSelector].base_high = (baseAddress >> 24) & 0xFF;
    gdt[segmentSelector].limit_low = (limitAddress & 0xFFFF);
    gdt[segmentSelector].granularity = ((limitAddress >> 16) & 0x0F);
    gdt[segmentSelector].granularity |= (granularity & 0xF0);
    gdt[segmentSelector].access = accessBit;
}


void gdtInit(){
    /* Setup the GDT pointer and limit */
    kernelGDT.limit = (sizeof(struct gdtEntry) * 3) - 1;
    kernelGDT.base = &gdt;

    /* Our NULL descriptor */
    setEntry(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    setEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    setEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    flushgTables();   
}