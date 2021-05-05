/*
    Defines Low Level Fault / Trap Handlers
*/


.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

//  0: Divide By Zero Exception
isr0:
    cli
    push   $0x0
    push   $0x0
    jmp bridgeToKernel

//  1: Debug Exception
isr1:
    cli
    push   $0x0
    push   $0x1
    jmp bridgeToKernel

//  2: Non Maskable Interrupt Exception
isr2:
    cli
    push   $0x0
    push   $0x2
    jmp bridgeToKernel

//  3: Int 3 Exception
isr3:
    cli
    push   $0x0
    push   $0x3
    jmp bridgeToKernel

//  4: INTO Exception
isr4:
    cli
    push   $0x0
    push   $0x4
    jmp bridgeToKernel

//  5: Out of Bounds Exception
isr5:
    cli
    push   $0x0
    push   $0x5
    jmp bridgeToKernel

//  6: Invalid Opcode Exception
isr6:
    cli
    push   $0x0
    push   $0x6
    jmp bridgeToKernel

//  7: Coprocessor Not Available Exception
isr7:
    cli
    push   $0x0
    push   $0x7
    jmp bridgeToKernel

//  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push   $0x8
    jmp bridgeToKernel

//  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push   $0x0
    push   $0x9
    jmp bridgeToKernel

// 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push   $0xa
    jmp bridgeToKernel

// 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push   $0xb
    jmp bridgeToKernel

// 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push   $0xc
    jmp bridgeToKernel

// 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push $0xd
    jmp bridgeToKernel

// 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push $0xe
    jmp bridgeToKernel

// 15: Reserved Exception
isr15:
    cli
    push $0x0
    push $0xf
    jmp bridgeToKernel

// 16: Floating Point Exception
isr16:
    cli
    push $0x0
    push $0x10
    jmp bridgeToKernel

// 17: Alignment Check Exception
isr17:
    cli
    push $0x0
    push $0x11
    jmp bridgeToKernel

// 18: Machine Check Exception
isr18:
    cli
    push $0x0
    push $0x12
    jmp bridgeToKernel

// 19: Reserved
isr19:
    cli
    push $0x0
    push $0x13
    jmp bridgeToKernel

// 20: Reserved
isr20:
    cli
    push $0x0
    push $0x14
    jmp bridgeToKernel

// 21: Reserved
isr21:
    cli
    push $0x0
    push $0x15
    jmp bridgeToKernel

// 22: Reserved
isr22:
    cli
    push $0x0
    push $0x16
    jmp bridgeToKernel

// 23: Reserved
isr23:
    cli
    push $0x0
    push $0x17
    jmp bridgeToKernel

// 24: Reserved
isr24:
    cli
    push $0x0
    push $0x18
    jmp bridgeToKernel

// 25: Reserved
isr25:
    cli
    push $0x0
    push $0x19
    jmp bridgeToKernel

// 26: Reserved
isr26:
    cli
    push $0x0
    push $0x1a
    jmp bridgeToKernel

// 27: Reserved
isr27:
    cli
    push $0x0
    push $0x1b
    jmp bridgeToKernel

// 28: Reserved
isr28:
    cli
    push $0x0
    push $0x1c
    jmp bridgeToKernel

// 29: Reserved
isr29:
    cli
    push $0x0
    push $0x1d
    jmp bridgeToKernel

// 30: Reserved
isr30:
    cli
    push $0x0
    push $0x1e
    jmp bridgeToKernel

// 31: Reserved
isr31:
    cli
    push $0x0
    push $0x1f
    jmp bridgeToKernel

.global bridgeToKernel

bridgeToKernel:
    pusha  
    push   %ds
    push   %es
    push   %fs
    push   %gs
    mov    $0x10,%ax
    mov    %eax,%ds
    mov    %eax,%es
    mov    %eax,%fs
    mov    %eax,%gs
    mov    %esp,%eax
    push   %eax
    mov    $faultHandler,%eax
    call   *%eax
    pop    %eax
    pop    %gs
    pop    %fs
    pop    %es
    pop    %ds
    popa   
    add    $0x8,%esp
    iret   



.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15

// 32: IRQ0
irq0:
    cli
    push $0x0
    push $0x20
    jmp irqBridgeToKernel

// 33: IRQ1
irq1:
    cli
    push $0x0
    push $0x21
    jmp irqBridgeToKernel

// 34: IRQ2
irq2:
    cli
    push $0x0
    push $0x22
    jmp irqBridgeToKernel

// 35: IRQ3
irq3:
    cli
    push $0x0
    push $0x23
    jmp irqBridgeToKernel

// 36: IRQ4
irq4:
    cli
    push $0x0
    push $0x24
    jmp irqBridgeToKernel

// 37: IRQ5
irq5:
    cli
    push $0x0
    push $0x25
    jmp irqBridgeToKernel

// 38: IRQ6
irq6:
    cli
    push $0x0
    push $0x26
    jmp irqBridgeToKernel

// 39: IRQ7
irq7:
    cli
    push $0x0
    push $0x27
    jmp irqBridgeToKernel

// 40: IRQ8
irq8:
    cli
    push $0x0
    push $0x28
    jmp irqBridgeToKernel

// 41: IRQ9
irq9:
    cli
    push $0x0
    push $0x29
    jmp irqBridgeToKernel

// 42: IRQ10
irq10:
    cli
    push $0x0
    push $0x2a
    jmp irqBridgeToKernel

// 43: IRQ11
irq11:
    cli
    push $0x0
    push $0x2b
    jmp irqBridgeToKernel

// 44: IRQ12
irq12:
    cli
    push $0x0
    push $0x2c
    jmp irqBridgeToKernel

// 45: IRQ13
irq13:
    cli
    push $0x0
    push $0x2d
    jmp irqBridgeToKernel

// 46: IRQ14
irq14:
    cli
    push $0x0
    push $0x2e
    jmp irqBridgeToKernel

// 47: IRQ15
irq15:
    cli
    push $0x0
    push $0x2f
    jmp irqBridgeToKernel


irqBridgeToKernel:
    pusha  
    push   %ds
    push   %es
    push   %fs
    push   %gs
    mov    $0x10,%ax
    mov    %eax,%ds
    mov    %eax,%es
    mov    %eax,%fs
    mov    %eax,%gs
    mov    %esp,%eax
    push   %eax
    mov    $interruptDispach,%eax
    call   *%eax
    pop    %eax
    pop    %gs
    pop    %fs
    pop    %es
    pop    %ds
    popa   
    add    $0x8,%esp
    iret   