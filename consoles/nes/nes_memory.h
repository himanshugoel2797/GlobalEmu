#ifndef _NES_MEMORY_H_
#define _NES_MEMORY_H_

#include "../../common.h"
#include "nes.h"

int memory_initialize();

u8 readByte(u16 offset);
void writeByte(u16 offset, u8 val);

u16 getAdjustedOffset(u16 offset);

u8* getMemory();

#endif
