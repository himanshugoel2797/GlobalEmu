TARGET = GlobalEmu

CC = clang
CFLAGS = -Wall -O3

OBJS = main.o consoles/console_mgr.o	\
	tools/endian.o	\
	consoles/nes/nes.o	consoles/nes/nes_loader.o	consoles/nes/nes_memory.o \
	cpus/mips/mips.o	\
	cpus/6502/6502.o cpus/6502/6502_cpuinfo.o cpus/6502/6502_instr.o

.PHONY: all

all:$(TARGET).exe
	cd tests/6502 && make

$(TARGET).exe:$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests:

clean:
	rm $(OBJS) *.exe
