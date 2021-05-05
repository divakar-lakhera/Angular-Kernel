.global idtFlush
.extern kernelIDTPointer
idtFlush:
    cli
    lidt (kernelIDTPointer)
    ret