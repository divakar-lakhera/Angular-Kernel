# MakeFile
# Written By: Divakar Lakhera
# Angular-Kernel

KL= Kernel/
OUTLOC= Kernel-Builds/
SOURCES=$(KL)bridge.o $(KL)kernel-loader.o $(KL)misc/portIO.o $(KL)drivers/VGA/vga_console.o $(KL)misc/string.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
LDFLAGS=-T linker.ld -m elf_i386
ASFLAGS=-f elf

all: $(SOURCES) link

clean:
	-rm $(KL)*.o $(OUTLOC)sysLoad.k

link:
	ld $(LDFLAGS) -o $(OUTLOC)sysLoad.k $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
