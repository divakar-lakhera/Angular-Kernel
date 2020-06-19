/*
   portIO.c
   Standard Port I/O Modules
   Written by: Divakar Lakhera
   Angular-Kernel
*/

#include "../headers/angular-kernel.h"

/*
   Outb
   Sends a byte of data to a port.
   Returns: Void
*/

void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

/*
   inb
   Recieves a byte of data from a port.
   Returns: byte (data recived from port)
*/

u8int inb(u16int port)
{
   u8int ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

/*
   inw
   Recieves a word (2 bytes) of data from a port.
   Returns: u16int(word) (data recived from port)
*/

u16int inw(u16int port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}