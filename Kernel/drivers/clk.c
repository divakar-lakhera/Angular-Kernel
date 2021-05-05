/*
    clk.c
    Kernel Time Keeper
    @author: Divakar Lakhera
*/

#include "../headers/angular-kernel.h"
#include "../headers/time.h"


void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outb(0x43, 0x36);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
unsigned long KERNEL_UP_TICKS = 0;
unsigned long KERNEL_UP_TIME = 0;

void clockIntHandler(struct regs *r)
{

    /* Increment our 'tick count' */
    KERNEL_UP_TICKS++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (KERNEL_UP_TICKS % 18 == 0)
    {
       // kprintf("One second has passed\n");
        KERNEL_UP_TIME++;
    }
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void installClock()
{
    /* Installs 'timer_handler' to IRQ0 */
    setHandler(0, clockIntHandler);
}

unsigned long kernelGetUpTime(){
    return KERNEL_UP_TIME;
}

unsigned long kernelGetUpTicks(){
    return KERNEL_UP_TICKS;
}