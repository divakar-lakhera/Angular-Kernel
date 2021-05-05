
test.o:     file format elf32-i386


Disassembly of section .text:

00000000 <_gdt_flush>:
   0:	0f 01 15 00 00 00 00 	lgdtl  0x0
   7:	66 b8 10 00          	mov    $0x10,%ax
   b:	8e d8                	mov    %eax,%ds
   d:	8e c0                	mov    %eax,%es
   f:	8e e0                	mov    %eax,%fs
  11:	8e e8                	mov    %eax,%gs
  13:	8e d0                	mov    %eax,%ss
  15:	ea 1c 00 00 00 08 00 	ljmp   $0x8,$0x1c

0000001c <flush2>:
  1c:	c3                   	ret    
