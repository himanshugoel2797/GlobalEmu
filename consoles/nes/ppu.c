#include "ppu.h"
#include "nes_memory.h"

PPU_REGISTER_FILE *ppu_regs;

int ppu_initialize()
{
        ppu_regs = getMemory() + PPU_REGISTER_LOC;
        memset(ppu_regs, 0, sizeof(PPU_REGISTER_FILE));
}
