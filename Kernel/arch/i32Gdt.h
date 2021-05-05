/*
    Intel x86 Global Discriptor Table (i32_GDT)
    Written By: Divakar Lakhera
    Angular Kernel
*/

#ifndef __KERNEL__GDT__
#define __KERNEL__GDT__

struct gdtEntry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct gdtPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void flushgTables();

#endif