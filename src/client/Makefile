BIN_ROOT=C:\Borland\BCC55\Bin
CC=$(BIN_ROOT)\bcc32.exe
INCLUDE_ROOT=C:\Borland\BCC55\Include
LIB_ROOT=C:\Borland\BCC55\Lib
OPT=-O2 -5 -d -ff -k- -OS -Q -X
MODEL=-W -WM
CFLAGS=-I$(INCLUDE_ROOT) -Izlib $(OPT) $(MODEL)
LDFLAGS=-L$(LIB_ROOT) -Llpng -Lzlib -L$(LIB_ROOT)\PSDK -W -WM -M

merc.exe:       dd.obj engine.obj main.obj inter.obj socket.obj sound.obj conv.obj options.obj makefile merc.res merc.def
        $(BIN_ROOT)\ilink32 /aa -L$(LIB_ROOT) -Llpng -Lzlib -L$(LIB_ROOT)\PSDK $(LIB_ROOT)\c0w32.obj dd.obj engine.obj main.obj inter.obj socket.obj sound.obj conv.obj options.obj,merc.exe,,cw32mt.lib import32.lib zlib.lib libpng.lib ddraw.lib dsound.lib,merc.def,merc.res

merc.res:       merc.rc merc.rh
        $(BIN_ROOT)\brcc32 merc.rc

socket.obj:     socket.c common.h inter.h

main.obj:       main.c common.h inter.h

clean:
        del *.obj
        del merc.exe
