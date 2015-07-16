#include "nes.h"

int nes_initialize()
{
        u8 *memory;
        //Allocate memory for the RAM
        memory = malloc(0x10000 * sizeof(u8));
        memset(memory, 0xFF, 0x10000 * sizeof(u8));

        _6502_initialize(memory);    //Initialize the cpu with as much RAM as the 16bit bus can address

        //Setup the system startup state
        memory[0x0008] = 0xF7;
        memory[0x0009] = 0xEF;
        memory[0x000A] = 0xDF;
        memory[0x000F] = 0xBF;

        //Frame IRQ enabled
        memory[0x4017] = 0x00;

        //All APU channels disabled
        memory[0x4015] = 0x00;

        for(int i = 0x4000; i <= 0x400F; i++) memory[i] = 0x00;

        return 0;
}

int nes_loadProgram(u8 *prog, size_t len)
{
        memcpy(_6502_getMemory(), prog, len);
        return 0;
}
