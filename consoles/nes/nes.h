#ifndef _NES_CONSOLE_H_
#define _NES_CONSOLE_H_

#include "../../common.h"
#include "../../cpus/6502/6502.h"

typedef struct {
        u8 persistent_PRGRAM;
        u8 mirror_mode;
        u8 mapperNumber;
}NES_CONFIG;

extern NES_CONFIG config;

/// Initialize the NES emulator
int nes_initialize();

/// Load a program into memory
int nes_loadProgram(u8 *prog, size_t len);

/// Load an iNES file into memory
int nes_load_iNES(const char *filename);

/// Execute a single NES instruction
int nes_processInstruction();

#endif
