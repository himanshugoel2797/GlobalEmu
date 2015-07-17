#include "nes_memory.h"

u8 *memory;

int memory_initialize()
{
        memory = malloc(0x10000 * sizeof(u8));
        memset(memory, 0xFF, 0x10000 * sizeof(u8));
}

u8 readByte(u16 offset)
{
        return memory[offset];
}

void writeByte(u16 offset, u8 val)
{
        memory[offset] = val;
}

u8* getMemory()
{
        return memory;
}
