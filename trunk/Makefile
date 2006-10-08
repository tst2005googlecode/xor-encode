!include "fastc.mak"

xe.exe: xe.obj xor_encode.obj
    "$(LINKER)" $(LINKERFLAGS) /VERSION:1.3 $(LINKERLIBS) "./bin/xe.obj" "./bin/xor_encode.obj" /OUT:"./xe.exe"

xe.obj : xe.c
    "$(CC)" $(CCFLAGS) xe.c

xor_encode.obj : xor_encode.c
    "$(CC)" $(CCFLAGS) xor_encode.c