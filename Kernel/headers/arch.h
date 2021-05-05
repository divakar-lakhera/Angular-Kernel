#ifndef KERNEL__ARCH__
#define KERNEL__ARCH__

void gdtInit();                                                  // Setup and Install new GDT
void idtUpdate();                                                // Setup and Install new IDT and setup Traps and Interrupt
void setHandler(int irq, void (*handler)(struct regs *r));       // Map Interrupt Handler for IRQ
void removeHandler(int irq);                                     // Free IRQ

#endif
