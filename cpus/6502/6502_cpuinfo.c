#include "6502_cpuinfo.h"

int _6502_isSPECIAL(u8 inst)
{
        switch(inst)
        {
        case _6502_PHP:
        case _6502_PLP:
        case _6502_PHA:
        case _6502_PLA:
        case _6502_DEY:
        case _6502_TAY:
        case _6502_INY:
        case _6502_INX:
        case _6502_CLC:
        case _6502_SEC:
        case _6502_CLI:
        case _6502_SEI:
        case _6502_TYA:
        case _6502_CLV:
        case _6502_CLD:
        case _6502_SED:
        case _6502_TXA:
        case _6502_TXS:
        case _6502_TAX:
        case _6502_TSX:
        case _6502_DEX:
        case _6502_NOP:
                return 1;
                break;
        default:
                return 0;
        }
        return 0;
}
