/*
    i32Int.c
    Declares IDT and Interrupt Routies.
    @Author: Divakar Lakhera
*/

#include "i32Int.h"                         //contains structs defining IDT
#include "../headers/angular-kernel.h"      
#include "traps.h"                          // contains exception msgs
#include "regs.h"                           // i32 i16 regs


struct idtEntry kernelIDT[256];
struct idtPointer kernelIDTPointer;



void setGateForIDT(unsigned char num, unsigned long baseAddress, unsigned short selector, unsigned char flags){
    
    /* The interrupt routine's base address */
    kernelIDT[num].base_lo = (baseAddress & 0xFFFF);
    kernelIDT[num].base_hi = (baseAddress >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */

    kernelIDT[num].sel = selector;
    kernelIDT[num].always0 = 0;
    kernelIDT[num].flags = flags;
}

void idtUpdate(){
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    kernelIDTPointer.limit = (sizeof (struct idtEntry) * 256) - 1;
    kernelIDTPointer.base = &kernelIDT;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&kernelIDT, 0, sizeof(struct idtEntry) * 256);

    /* Add any new ISRs to the IDT here using setGateForIDT */
    setupFaultGates();
    mapInterrupt();

    /* Points the processor's internal register to the new IDT */
    idtFlush();
}

// Setup Gates

/* This is a very repetitive function... it's not hard, it's
*  just annoying. As you can see, we set the first 32 entries
*  in the IDT to the first 32 ISRs. We can't use a for loop
*  for this, because there is no way to get the function names
*  that correspond to that given entry. We set the access
*  flags to 0x8E. This means that the entry is present, is
*  running in ring 0 (kernel level), and has the lower 5 bits
*  set to the required '14', which is represented by 'E' in
*  hex. */

void setupFaultGates()
{
    setGateForIDT(0, (unsigned)isr0, 0x08, 0x8E);
    setGateForIDT(1, (unsigned)isr1, 0x08, 0x8E);
    setGateForIDT(2, (unsigned)isr2, 0x08, 0x8E);
    setGateForIDT(3, (unsigned)isr3, 0x08, 0x8E);
    setGateForIDT(4, (unsigned)isr4, 0x08, 0x8E);
    setGateForIDT(5, (unsigned)isr5, 0x08, 0x8E);
    setGateForIDT(6, (unsigned)isr6, 0x08, 0x8E);
    setGateForIDT(7, (unsigned)isr7, 0x08, 0x8E);

    setGateForIDT(8, (unsigned)isr8, 0x08, 0x8E);
    setGateForIDT(9, (unsigned)isr9, 0x08, 0x8E);
    setGateForIDT(10, (unsigned)isr10, 0x08, 0x8E);
    setGateForIDT(11, (unsigned)isr11, 0x08, 0x8E);
    setGateForIDT(12, (unsigned)isr12, 0x08, 0x8E);
    setGateForIDT(13, (unsigned)isr13, 0x08, 0x8E);
    setGateForIDT(14, (unsigned)isr14, 0x08, 0x8E);
    setGateForIDT(15, (unsigned)isr15, 0x08, 0x8E);

    setGateForIDT(16, (unsigned)isr16, 0x08, 0x8E);
    setGateForIDT(17, (unsigned)isr17, 0x08, 0x8E);
    setGateForIDT(18, (unsigned)isr18, 0x08, 0x8E);
    setGateForIDT(19, (unsigned)isr19, 0x08, 0x8E);
    setGateForIDT(20, (unsigned)isr20, 0x08, 0x8E);
    setGateForIDT(21, (unsigned)isr21, 0x08, 0x8E);
    setGateForIDT(22, (unsigned)isr22, 0x08, 0x8E);
    setGateForIDT(23, (unsigned)isr23, 0x08, 0x8E);

    setGateForIDT(24, (unsigned)isr24, 0x08, 0x8E);
    setGateForIDT(25, (unsigned)isr25, 0x08, 0x8E);
    setGateForIDT(26, (unsigned)isr26, 0x08, 0x8E);
    setGateForIDT(27, (unsigned)isr27, 0x08, 0x8E);
    setGateForIDT(28, (unsigned)isr28, 0x08, 0x8E);
    setGateForIDT(29, (unsigned)isr29, 0x08, 0x8E);
    setGateForIDT(30, (unsigned)isr30, 0x08, 0x8E);
    setGateForIDT(31, (unsigned)isr31, 0x08, 0x8E);
}


void faultHandler(struct regs *r)
{
    if (r->int_no < 32)
    {
        kprintf(systemTrapMessages[r->int_no]);
        kprintf(" Exception. System Halted!\n");
        for (;;);
    }
}

// IRQ section start

void *irqHandlerPointer[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void setHandler(int irq, void (*handler)(struct regs *r)){
    // TODO: Do sanitation check
    irqHandlerPointer[irq] = handler;
}

void removeHandler(int irq){
    // TODO: Do sanitation check
    irqHandlerPointer[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irqRemap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void mapInterrupt()
{
    irqRemap();

    setGateForIDT(32, (unsigned)irq0, 0x08, 0x8E);
    setGateForIDT(33, (unsigned)irq1, 0x08, 0x8E);
    setGateForIDT(34, (unsigned)irq2, 0x08, 0x8E);
    setGateForIDT(35, (unsigned)irq3, 0x08, 0x8E);
    setGateForIDT(36, (unsigned)irq4, 0x08, 0x8E);
    setGateForIDT(37, (unsigned)irq5, 0x08, 0x8E);
    setGateForIDT(38, (unsigned)irq6, 0x08, 0x8E);
    setGateForIDT(39, (unsigned)irq7, 0x08, 0x8E);

    setGateForIDT(40, (unsigned)irq8, 0x08, 0x8E);
    setGateForIDT(41, (unsigned)irq9, 0x08, 0x8E);
    setGateForIDT(42, (unsigned)irq10, 0x08, 0x8E);
    setGateForIDT(43, (unsigned)irq11, 0x08, 0x8E);
    setGateForIDT(44, (unsigned)irq12, 0x08, 0x8E);
    setGateForIDT(45, (unsigned)irq13, 0x08, 0x8E);
    setGateForIDT(46, (unsigned)irq14, 0x08, 0x8E);
    setGateForIDT(47, (unsigned)irq15, 0x08, 0x8E);
}

void interruptDispach(struct regs *r)
{
    /* This is a blank function pointer */
    void (*handler)(struct regs *r);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = irqHandlerPointer[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outb(0x20, 0x20);
}