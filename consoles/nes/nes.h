#ifndef _NES_CONSOLE_H_
#define _NES_CONSOLE_H_

#include "../../cpus/6502/6502.h"

/// Initialize the NES emulator
int nes_initialize();

/// Load a program into memory
int nes_loadProgram(u8 *prog, size_t len);

#endif
