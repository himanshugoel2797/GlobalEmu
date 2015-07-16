AS = ../../../cc65/bin/ca65
LD = ../../../cc65/bin/ld65

OBJS = generalTest.bin

.PHONY: clean all

all:clean $(OBJS)

%.bin:%.S
	$(AS) --cpu 6502 $< -o $(@:.bin=.6502)
	$(LD) -t none $(@:.bin=.6502) -o $@

clean:
	rm -f $(OBJS)
