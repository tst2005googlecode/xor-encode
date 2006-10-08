#PATHS
CCPATH  = d:\Program Files\Microsoft Visual Studio 8\VC

#COMPILER
CC      = $(CCPATH)\bin\cl.exe
CCFLAGS = /I"$(CCPATH)\include" /Ox /Ob2 /Oi /Ot /Oy /GT /GL /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_UNICODE" /D "UNICODE" /GF /FD /MD /GS- /Za /GR- /WX /Fo.\bin\\ /Fd.\bin\vc80.pdb /Fa.\bin\\ /FAs /W4 /nologo /c /Wp64 /TC

#LINKER
LINKER      = $(CCPATH)\bin\link.exe
LINKERFLAGS = /LIBPATH:"$(CCPATH)\lib" /INCREMENTAL:NO /NOLOGO /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /LTCG /MACHINE:X86 /RELEASE /NODEFAULTLIB
LINKERLIBS  = msvcrt.lib kernel32.lib