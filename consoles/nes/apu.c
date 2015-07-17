#include "apu.h"
#include "nes_memory.h"

APU_REGISTER_FILE *apu_regs;

int apu_initialize()
{
        apu_regs = getMemory() + APU_REGISTER_OFFSET;
        memset(apu_regs, 0, sizeof(APU_REGISTER_FILE));
}
