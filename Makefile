TARGET = MipsEmu

CC = clang
CFLAGS = -Wall -O3

OBJS = main.o

.PHONY: $(TARGET).exe

$(TARGET).exe:$(OBJS)
	$(CC) $< -o $@
