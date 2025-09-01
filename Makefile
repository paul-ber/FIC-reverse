CC=cl
CFLAGS=/nologo /O2 /I"include" /DWIN32_LEAN_AND_MEAN /D_WIN32_WINNT=0x0601
LDFLAGS=/SUBSYSTEM:CONSOLE /nologo
LIBS=kernel32.lib user32.lib ws2_32.lib

SRCDIR=src
SOURCES=$(SRCDIR)/*.c
TARGET=novalocker.exe

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) /Fe:$(TARGET) /link $(LDFLAGS)

clean:
	del /f $(TARGET) *.obj *.pdb *.ilk

test:
	@echo "TODO: Implement tests"
