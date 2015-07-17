#ifndef _CPU_6502_H_
#define _CPU_6502_H_
#include "../../common.h"

#define _6502_ENDIAN LITTLE_ENDIAN

/// Initialize 6502 processor
int _6502_initialize(u8 *mem,u8(*readByte)(u16), void(*writeByte)(u16, u8));

/// Process a single instruction
int _6502_processInstruction();

/// Get a register value
u8 _6502_getRegister(int reg);

/// Set a register value
int _6502_setRegister(int reg, u8 val);

/// Get PC value
u16 _6502_getPC();

/// Set PC value
int _6502_setPC(u16 val);

/// Get SP value
u16 _6502_getSP();

/// Set SP value
int _6502_setSP(u16 val);

#endif
