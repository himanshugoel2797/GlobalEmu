#include "nes.h"
#include "nes_memory.h"
#include "apu.h"
#include "ppu.h"

NES_CONFIG config;

int nes_initialize()
{
        //Allocate memory for the RAM
        memory_initialize();

        u8 *memory = getMemory();
        ppu_initialize(); //Setup the ppu
        apu_initialize(); //Setup the apu

        _6502_initialize(memory, readByte, writeByte);    //Initialize the cpu with as much RAM as the 16bit bus can address

        //Setup the system startup state
        memory[0x0008] = 0xF7;
        memory[0x0009] = 0xEF;
        memory[0x000A] = 0xDF;
        memory[0x000F] = 0xBF;

        return 0;
}

int nes_processInstruction()
{
        return _6502_processInstruction();
}
