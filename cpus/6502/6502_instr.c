#include "6502_instr.h"

int _6502_ORA_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset = 0;

        switch(b)
        {
        case _6502_A_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
        }
        break;
        }

        generalPurposeRegisters[REGS_ACCUM] |= memory[offset];
        //Update the flags register
        _6502_storeNZ(REGS_ACCUM);

        return cycleCount;
}

int _6502_AND_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;

        u16 offset = 0;

        switch(b)
        {
        case _6502_A_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_ACCUM] &= memory[offset];
        //Update the flags register
        _6502_storeNZ(REGS_ACCUM);

        return cycleCount;
}

int _6502_EOR_process(u8 a, u8 b, u8 c)
{

        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_A_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_ACCUM] ^= memory[offset];
        //Update the flags register
        _6502_storeNZ(REGS_ACCUM);

        return cycleCount;
}

int _6502_ADC_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_A_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];

        u16 t = 0;
        if(IsSet(STATUS_DEC))
        {
                t = bcd(generalPurposeRegisters[REGS_ACCUM]) + bcd(memory[offset]) + IsSet(STATUS_CARRY);
                status->C = (t > 99);
        }else{
                t = generalPurposeRegisters[REGS_ACCUM] + memory[offset] + IsSet(STATUS_CARRY);
                status->C = (t > 255);
        }

        status->O = (generalPurposeRegisters[REGS_ACCUM] >> 7) != ((t >> 7) & 1);
        status->N = (t >> 7) & 1;
        status->Z = (t == 0);

        generalPurposeRegisters[REGS_ACCUM] = t & 0xFF;


        return cycleCount;
}

int _6502_STA_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 5;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 6;
        }
        break;
        default:
                return -1;
                break;
        }

        memory[offset] = generalPurposeRegisters[REGS_ACCUM];

        return cycleCount;
}

int _6502_LDA_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_A_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_ACCUM] = memory[offset];
        _6502_storeNZ(REGS_ACCUM);

        return cycleCount;
}

int _6502_CMP_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_A_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_ACCUM] - memory[offset];
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = t >> 7;
        status->C = (generalPurposeRegisters[REGS_ACCUM] >= memory[offset]);
        status->Z = (t == 0);

        printf("\nCMP against %08x\n", memory[offset]);

        return cycleCount;
}

int _6502_SBC_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_A_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_A_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (memory[pc - 1] + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = memory[offsetA] | (memory[offsetA + 1] << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (memory[memory[pc - 1]] | (memory[memory[pc - 1] + 1]) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        s8 t = 0;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];

        if(IsSet(STATUS_DEC))
        {
                t = bcd(generalPurposeRegisters[REGS_ACCUM]) - bcd(memory[offset]) - !IsSet(STATUS_CARRY);
                status->O = (t > 99 | t < 0);
        }else{
                t = generalPurposeRegisters[REGS_ACCUM] - memory[offset] - !IsSet(STATUS_CARRY);
        }

        s16 A = generalPurposeRegisters[REGS_ACCUM];
        s16 M = memory[offset];

        //if( A >= 0 && M >= 0 && t < 0) status->O = 1;
        //else if(A < 0 && M < 0 && t >= 0) status->O = 1;
        //else status->O = 0;

        status->O = (M > A && M > 0 && t > A);

        printf("\n%d,%d,%d\n", t, A, M);

        status->C = (generalPurposeRegisters[REGS_ACCUM] >= memory[offset]);
        status->N = (t >> 7) & 1;
        status->Z = (t == 0);

        generalPurposeRegisters[REGS_ACCUM] = (t & 0xFF);


        return cycleCount;
}

//Mode B
int _6502_ASL_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u8 *loc = NULL;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM:
                loc = &generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                break;
        case _6502_B_ZR_PAGE:
                loc = &memory[memory[pc - 1]];
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                loc = &memory[(generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                loc = &memory[memory[pc - 2] | memory[pc - 1] << 8];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                loc = &memory[(memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X]];
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        status->C = *loc >> 7;
        *loc = (*loc << 1) & 0xFE;
        status->N = (*loc >> 7);
        status->Z = (*loc == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_ROL_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u8 *loc = NULL;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM:
                loc = &generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                break;
        case _6502_B_ZR_PAGE:
                loc = &memory[memory[pc - 1]];
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                loc = &memory[(generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                loc = &memory[memory[pc - 2] | memory[pc - 1] << 8];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                loc = &memory[(memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X]];
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        s8 t = *loc >> 7;
        *loc = (*loc << 1) & 0xFE;
        *loc = *loc | status->C;
        status->C = t;
        status->N = (*loc >> 7);
        status->Z = (*loc == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_LSR_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u8 *loc = NULL;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM:
                loc = &generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                break;
        case _6502_B_ZR_PAGE:
                loc = &memory[memory[pc - 1]];
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                loc = &memory[(generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                loc = &memory[memory[pc - 2] | memory[pc - 1] << 8];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                loc = &memory[(memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X]];
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        status->C = *loc & 1;
        *loc = (*loc >> 1) & 0x7F;
        status->N = 0;
        status->Z = (*loc == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_ROR_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u8 *loc = NULL;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM:
                loc = &generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                break;
        case _6502_B_ZR_PAGE:
                loc = &memory[memory[pc - 1]];
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                loc = &memory[(generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                loc = &memory[memory[pc - 2] | memory[pc - 1] << 8];
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                loc = &memory[(memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X]];
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        s8 t = *loc & 1;
        *loc = (*loc >> 1) & 0x7F;
        *loc = *loc | (status->C ? 0x80 : 0x00);
        status->C = t;
        status->N = (*loc >> 7);
        status->Z = (*loc == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_STX_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_B_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                //Special Case, Zero Page, Y
                offset = (generalPurposeRegisters[REGS_Y] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        memory[offset] = generalPurposeRegisters[REGS_X];

        return cycleCount;
}

int _6502_LDX_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_B_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_B_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                //Special case, actually Zero Page, Y
                offset = (generalPurposeRegisters[REGS_Y] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_X] = memory[offset];
        _6502_storeNZ(REGS_X);

        return cycleCount;
}

int _6502_DEC_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_B_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        memory[offset]--;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = (memory[offset] >> 7);
        status->Z = (memory[offset] == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_INC_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_B_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        memory[offset]++;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = (memory[offset] >> 7);
        status->Z = (memory[offset] == 0) ? 1 : 0;

        return cycleCount;
}



//Mode C
int _6502_BIT_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_C_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_C_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_ACCUM] & memory[offset];

        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = (memory[offset] >> 7) & 1;
        status->O = (memory[offset] >> 6) & 1;
        status->Z = (t == 0);

        return cycleCount;
}

//Represents the indirect jump instruction
int _6502_JMP_process(u8 a, u8 b, u8 c)
{
        u16 targetA = memory[pc - 2] | (memory[pc - 1] << 8);
        u16 target = memory[targetA] | (memory[targetA + 1] << 8);
        pc = target;

        return 5; //cycleCount
}

//Represents the absolute jump instruction
int _6502_JMP_A_process(u8 a, u8 b, u8 c)
{
        u16 target = memory[pc - 2] | (memory[pc - 1] << 8);
        pc = target;

        return 3; //cycleCount
}

int _6502_STY_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_C_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_C_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_C_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        memory[offset] = generalPurposeRegisters[REGS_Y];

        return cycleCount;
}

int _6502_LDY_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_C_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_C_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_C_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + memory[pc - 1]) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_C_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        case _6502_C_ABS_X:
        {
                offset = (memory[pc - 2] | memory[pc - 1] << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < memory[pc - 1] << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_Y] = memory[offset];
        _6502_storeNZ(REGS_Y);

        return cycleCount;
}

int _6502_CPY_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_C_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_C_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_C_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_Y] - memory[offset];
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = t >> 7;
        status->C = (generalPurposeRegisters[REGS_Y] >= memory[offset]);
        status->Z = (t == 0);

        return cycleCount;
}

int _6502_CPX_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_C_IMM:
                offset = pc - 1;
                cycleCount = 2;
                break;
        case _6502_C_ZR_PAGE:
                offset = memory[pc - 1];
                cycleCount = 3;
                break;
        case _6502_C_ABS:
        {
                offset = memory[pc - 2] | memory[pc - 1] << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_X] - memory[offset];
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = t >> 7;
        status->C = (generalPurposeRegisters[REGS_X] >= memory[offset]);
        status->Z = (t == 0);

        return cycleCount;
}
