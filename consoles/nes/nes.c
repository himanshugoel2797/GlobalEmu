#include "nes.h"

int nes_initialize()
{
        _6502_initialize((u16)-1);    //Initialize the cpu with as much RAM as the 16bit bus can address

        return 0;
}
