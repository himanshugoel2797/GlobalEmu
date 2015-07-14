#ifndef _CPU_6502_CPUINFO_H_
#define _CPU_6502_CPUINFO_H_
#include "../../common.h"

typedef enum {
        STATUS_CARRY = 0,
        STATUS_ZERO = 1,
        STATUS_INT = 2,
        STATUS_DEC = 3,
        STATUS_BRK = 4,
        STATUS_UNUSED = 5,  //Must always be 1
        STATUS_OVRF = 6,
        STATUS_SIGN = 7
}_6502_STATUS_BITS;

typedef enum {
        ACCUM = 0,
        X = 1,
        Y = 2,
        STATUS = 3
}_6502_REGS;

#define REAL_SP_START 0x01ff
#define REAL_SP_END 0x0100
#define SOFT_SP_START 0xff
#define SOFT_SP_END 0x00

typedef enum {
        A = 1,
        B = 2,
        C = 0
}_6502_C_VALS;

typedef enum {
        _6502_ORA = 0,
        _6502_AND = 1,
        _6502_EOR = 2,
        _6502_ADC = 3,
        _6502_STA = 4,
        _6502_LDA = 5,
        _6502_CMP = 6,
        _6502_SBC = 7
}_6502_A_OPS;

typedef enum {
        _6502_A_ZR_PAGE_IND_X = 0,
        _6502_A_ZR_PAGE = 1,
        _6502_A_IMM = 2,
        _6502_A_ABS = 3,
        _6502_A_ZR_PAGE_IND_Y = 4,
        _6502_A_ZR_PAGE_X = 5,
        _6502_A_ABS_Y = 6,
        _6502_A_ABS_X = 7
}_6502_A_ADDRMODE;

typedef enum {
        _6502_ASL = 0,
        _6502_ROL = 1,
        _6502_LSR = 2,
        _6502_ROR = 3,
        _6502_STX = 4,
        _6502_LDX = 5,
        _6502_DEC = 6,
        _6502_INC = 7
}_6502_B_OPS;

typedef enum {
        _6502_B_IMM = 0,
        _6502_B_ZR_PAGE = 1,
        _6502_B_ACCUM = 2,
        _6502_B_ABS = 3,
        _6502_B_ZR_PAGE_X = 5,
        _6502_B_ABS_X = 7
}_6502_B_ADDRMODE;

typedef enum {
        _6502_BIT = 1,
        _6502_JMP = 2,
        _6502_JMP_A = 3,
        _6502_STY = 4,
        _6502_LDY = 5,
        _6502_CPY = 6,
        _6502_CPX = 7
}_6502_C_OPS;

typedef enum {
        _6502_C_IMM = 0,
        _6502_C_ZR_PAGE = 1,
        _6502_C_ABS = 3,
        _6502_C_ZR_PAGE_X = 5,
        _6502_C_ABS_X = 7
}_6502_C_ADDRMODE;

//Opcodes
typedef enum {
        _6502_PHP = 0x08,
        _6502_PLP = 0x28,
        _6502_PHA = 0x48,
        _6502_PLA = 0x68,
        _6502_DEY = 0x88,
        _6502_TAY = 0xA8,
        _6502_INY = 0xC8,
        _6502_INX = 0xE8,
        _6502_CLC = 0x18,
        _6502_SEC = 0x38,
        _6502_CLI = 0x58,
        _6502_SEI = 0x78,
        _6502_TYA = 0x98,
        _6502_CLV = 0xB8,
        _6502_CLD = 0xD8,
        _6502_SED = 0xF8,
        _6502_TXA = 0x8A,
        _6502_TXS = 0x9A,
        _6502_TAX = 0xAA,
        _6502_TSX = 0xBA,
        _6502_DEX = 0xCA,
        _6502_NOP = 0xEA,
}_6502_SPECIAL_OPS;

int _6502_isSPECIAL(u8 inst);
#endif
