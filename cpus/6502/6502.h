#ifndef _CPU_6502_H_
#define _CPU_6502_H_
#include "../../common.h"

#define _6502_ENDIAN LITTLE_ENDIAN

/// Initialize 6502 processor
int _6502_initialize(size_t memorySize);

/// Get a pointer to the memory
u8* _6502_getMemory();

/// Process a single instruction
int _6502_processInstruction();

#endif
