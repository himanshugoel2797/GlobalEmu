#include "nes_memory.h"

u8 *memory;

int memory_initialize()
{
        memory = malloc(0x10000 * sizeof(u8));
        memset(memory, 0xFF, 0x10000 * sizeof(u8));

        return 0;
}

u8 readByte(u16 offset)
{
        offset = getAdjustedOffset(offset);
        return memory[offset];
}

void writeByte(u16 offset, u8 val)
{
        offset = getAdjustedOffset(offset);
        memory[offset] = val;
}

u16 getAdjustedOffset(u16 offset)
{
        //Account for memory mirroring
        if(offset >= 0x0800 && offset < 0x2000)
        {
                offset = offset % 0x0800;
        }else if(offset >= 0x2008 && offset < 0x4000)
        {
                offset = 0x2000 + (offset % 0x2000);
        }

        return offset;
}

u8* getMemory(){
        return memory;
}
