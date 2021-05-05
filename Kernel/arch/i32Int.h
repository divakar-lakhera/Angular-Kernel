/*
    i32Int.h
    @Author: Divakar Lakhera
*/

#ifndef __KERNEL__IDT
#define __KERNEL__IDT

/* Defines an IDT entry */
struct idtEntry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idtPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void setupFaultGates();
void mapInterrupt();
extern void idtFlush();

#endif