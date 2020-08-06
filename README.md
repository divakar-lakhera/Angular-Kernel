# Angular Kernel
>  AngularOS is a monolithic kernel written to grasp better understanding of how an operating system works.
>  
>  Goal of this project is not to build a complete OS but is to build a minimal operating system which contains all the basic functionalities of an operating system.

[![GPLv3 license](https://img.shields.io/badge/License-GPLv3-blue.svg)](http://perso.crans.org/besson/LICENSE.html) ![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)
[![Generic badge](https://img.shields.io/badge/Language-C-<COLOR>.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/Kernel-Module-red.svg)](https://shields.io/) ![GitHub contributors](https://img.shields.io/github/contributors/Naereen/StrapDown.js.svg)

# Building Angular-Kernel

> Clone repo

    git clone https://github.com/divakar-lakhera/Angular-Kernel.git
   

> Using Terminal (Requires GNU GCC and build-tools)

    $ make clean
    $ make
   >Using any disk image editor ( ex. PowerISO) write boot.img
   

    from Kernel-Builds/
    open boot.img using PowerISO
    replace old "sysLoad.k" from latest built sysLoad.k from Kernel-Builds
    
   # Testing Kernel
 Testing Environment : 
> Bochs (x86 Emulator) & 128 MB Ram

> Test the boot.img by clicking on test_boot.bxrc (Requires Bochs installed)
