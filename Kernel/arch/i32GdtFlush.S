/*
    i32GdtFlush.S
    Flushes previously defined GDT and loads now GDT using 'lgdt' instruction.
*/

#define ASM_FILE  1

.global flushgTables
.extern kernelGDT
flushgTables:
    cli
    lgdt   (kernelGDT)
    mov    $0x10,%ax
    mov    %eax,%ds
    mov    %eax,%es
    mov    %eax,%fs
    mov    %eax,%gs
    mov    %eax,%ss
    ljmp   $0x8,$flush2
flush2:
    ret