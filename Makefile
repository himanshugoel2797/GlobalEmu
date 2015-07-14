TARGET = GlobalEmu

CC = clang
CFLAGS = -Wall -O3

OBJS = main.o consoles/console_mgr.o	\
	tools/endian.o	\
	consoles/nes/nes.o	\
	cpus/mips/mips.o cpus/6502/6502.o cpus/6502/6502_cpuinfo.o

.PHONY: $(TARGET).exe

$(TARGET).exe:$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) *.exe
