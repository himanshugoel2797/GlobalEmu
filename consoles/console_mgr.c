#include "console_mgr.h"

//Include for the NES console
#include "nes/nes.h"

int console_mgr_initialize(CONSOLES c)
{
        switch(c)
        {
        case NES:
                return nes_initialize();
                break;
        default:
                return -1;
                break;
        }
        return -1;
}
