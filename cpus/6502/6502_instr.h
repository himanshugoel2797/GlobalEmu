#ifndef _CPU_6502_INSTR_H_
#define _CPU_6502_INSTR_H_

#include "6502.h"
#include "6502_cpuinfo.h"
#include "../../common.h"

int _6502_ORA_process(u8 a, u8 b, u8 c);
int _6502_AND_process(u8 a, u8 b, u8 c);
int _6502_EOR_process(u8 a, u8 b, u8 c);
int _6502_ADC_process(u8 a, u8 b, u8 c);
int _6502_STA_process(u8 a, u8 b, u8 c);
int _6502_LDA_process(u8 a, u8 b, u8 c);
int _6502_CMP_process(u8 a, u8 b, u8 c);
int _6502_SBC_process(u8 a, u8 b, u8 c);

int _6502_ASL_process(u8 a, u8 b, u8 c);
int _6502_ROL_process(u8 a, u8 b, u8 c);
int _6502_LSR_process(u8 a, u8 b, u8 c);
int _6502_ROR_process(u8 a, u8 b, u8 c);
int _6502_STX_process(u8 a, u8 b, u8 c);
int _6502_LDX_process(u8 a, u8 b, u8 c);
int _6502_DEC_process(u8 a, u8 b, u8 c);
int _6502_INC_process(u8 a, u8 b, u8 c);


int _6502_BIT_process(u8 a, u8 b, u8 c);
int _6502_JMP_process(u8 a, u8 b, u8 c);
int _6502_JMP_A_process(u8 a, u8 b, u8 c);
int _6502_STY_process(u8 a, u8 b, u8 c);
int _6502_LDY_process(u8 a, u8 b, u8 c);
int _6502_CPY_process(u8 a, u8 b, u8 c);
int _6502_CPX_process(u8 a, u8 b, u8 c);

static inline void _6502_storeNZ(int reg)
{
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = (generalPurposeRegisters[reg] >> 7);
        status->Z = (generalPurposeRegisters[reg] == 0) ? 1 : 0;
}

static inline int bcd(u8 val)
{
        return 10 * (val & 0xF0) + val & 0x0F;
}

#endif
