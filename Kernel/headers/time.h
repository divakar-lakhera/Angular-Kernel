/*
    time.h
    Kernel Time-Keeping Functions.
*/

#ifndef KERNEL_TIME__
#define KERNEL_TIME__
#include "../arch/regs.h"

void installClock();
void clockIntHandler(struct regs *r);
unsigned long kernelGetUpTime();
unsigned long kernelGetUpTicks();

#endif 

