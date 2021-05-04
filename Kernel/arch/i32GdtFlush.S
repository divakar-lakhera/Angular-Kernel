#define ASM_FILE  1

.global flushgTables
.extern kernelGDT
flushgTables:
    lgdt kernelGDT
    mov %ax, 0x10
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    jmp $0x08,$flush2
flush2:
    ret