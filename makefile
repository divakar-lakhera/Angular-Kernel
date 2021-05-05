# MakeFile
# Written By: Divakar Lakhera
# Angular-Kernel

KL= Kernel/
ARCH = Kernel/arch/
DRV = Kernel/drivers/
OUTLOC= Kernel-Builds/
SOURCES=$(KL)bridge.o $(KL)kernel-loader.o $(KL)misc/portIO.o $(KL)drivers/VGA/vga_console.o $(KL)misc/string.o \
	$(KL)arch/i32Gdt.o $(ARCH)/i32Int.o $(ARCH)i32GdtFlush.o $(ARCH)i32IntFlush.o $(ARCH)traps.o\
	$(DRV)clk.o
ASMS = $(KL)bridge.s
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
LDFLAGS=-T linker.ld -m elf_i386
ASFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
NASMF = -f elf32



all: $(SOURCES) link

clean:
	-rm $(KL)*.o $(OUTLOC)sysLoad.k $(OUTLOC)/img-content/boot/sysLoad.k $(ARCH)*.o $(DRV)*.o $(DRV)VGA/*.o

link:
	ld $(LDFLAGS) -o $(OUTLOC)sysLoad.k $(SOURCES)

#.s.o:
#	nasm $(NASMF) $<

