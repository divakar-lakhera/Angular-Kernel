#! /bin/bash
mkdir -p Kernel-Builds/img-content/
mkdir -p Kernel-Builds/img-content/boot/
mkdir -p Kernel-Builds/img-content/boot/grub/
cp Kernel-Builds/sysLoad.k Kernel-Builds/img-content/boot/sysLoad.k
cat > Kernel-Builds/img-content/boot/grub/grub.cfg << EOF
menuentry "Angular" {
	multiboot /boot/sysLoad.k
}
EOF
grub-mkrescue -o angular.iso Kernel-Builds/img-content/