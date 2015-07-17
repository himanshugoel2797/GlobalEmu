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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1)+1)) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
        }
        break;
        }

        generalPurposeRegisters[REGS_ACCUM] |= readMem(offset);
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1) + 1)) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_ACCUM] &= readMem(offset);
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1) + 1)) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_ACCUM] ^= readMem(offset);
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1) + 1)) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];

        u8 t = 0;
        u16 tmp = 0;
        if(IsSet(STATUS_DEC))
        {
                tmp = bcd(generalPurposeRegisters[REGS_ACCUM]) + bcd(readMem(offset)) + IsSet(STATUS_CARRY);
                status->C = (tmp > 99);
        }else{
                tmp = generalPurposeRegisters[REGS_ACCUM] + readMem(offset) + IsSet(STATUS_CARRY);
                status->C = (tmp > 255);
        }

        t = tmp & 0xFF;
        status->O = ((~(generalPurposeRegisters[REGS_ACCUM] ^ readMem(offset)))&(generalPurposeRegisters[REGS_ACCUM] ^ t)&0x80) == 0x80;
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 5;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1) + 1)) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 6;
        }
        break;
        default:
                return -1;
                break;
        }

        writeMem(offset, generalPurposeRegisters[REGS_ACCUM]);

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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1) + 1)) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_ACCUM] = readMem(offset);
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1) + 1)) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 5;
                if((offset & 0xFF) < generalPurposeRegisters[REGS_Y]) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_ACCUM] - readMem(offset);
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = t >> 7;
        status->C = (generalPurposeRegisters[REGS_ACCUM] >= readMem(offset));
        status->Z = (t == 0);

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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_A_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_A_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ABS_Y:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        case _6502_A_ZR_PAGE_IND_X:
        {
                u16 offsetA = (readMem(pc - 1) + generalPurposeRegisters[REGS_X]) & 0xFF;
                offset = readMem(offsetA) | (readMem(offsetA + 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_A_ZR_PAGE_IND_Y:
        {
                offset = (readMem(readMem(pc - 1)) | (readMem(readMem(pc - 1) + 1)) << 8) + generalPurposeRegisters[REGS_Y];
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
                t = bcd(generalPurposeRegisters[REGS_ACCUM]) - bcd(readMem(offset)) - !IsSet(STATUS_CARRY);
                status->O = (t > 99 | t < 0);
        }else{
                t = (s8)generalPurposeRegisters[REGS_ACCUM] - (s8)readMem(offset) - !IsSet(STATUS_CARRY);
        }

        s8 A = generalPurposeRegisters[REGS_ACCUM];
        s8 M = readMem(offset);

        if( A >= 0 && M >= 0 && t < 0) status->O = 1;
        else if(A < 0 && M < 0 && A > M && t < 0) status->O = 1;
        else if(A < 0 && M < 0 && A < M && t >= 0) status->O = 1;
        else if(A >= 0 && M < 0 && (-M) < A && t <= 0) status->O = 1;
        else status->O = 0;

        status->C = (t >> 7) != (A >> 7);
        status->C = ((~(generalPurposeRegisters[REGS_ACCUM] ^ readMem(offset)))&(generalPurposeRegisters[REGS_ACCUM] ^ t)&0x80) == 0x80;

        status->N = (t >> 7) & 1;
        status->Z = (t == 0);

        generalPurposeRegisters[REGS_ACCUM] = (t & 0xFF);


        return cycleCount;
}

//Mode B
int _6502_ASL_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM:
        {
                u8 *loc = &generalPurposeRegisters[REGS_ACCUM];
                status->C = *loc >> 7;
                *loc = (*loc << 1) & 0xFE;
                status->N = (*loc >> 7);
                status->Z = (*loc == 0) ? 1 : 0;
                cycleCount = 2;
                return cycleCount;
        }
        break;
        case _6502_B_ZR_PAGE:
                offset = readMem(pc - 1);
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        status->C = readMem(offset) >> 7;
        writeMem(offset, (readMem(offset) << 1) & 0xFE);
        status->N = (readMem(offset) >> 7);
        status->Z = (readMem(offset) == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_ROL_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM: {
                u8 *loc = &generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;


                s8 t = *loc >> 7;
                *loc = (*loc << 1) & 0xFE;
                *loc = *loc | status->C;
                status->C = t;
                status->N = (*loc >> 7);
                status->Z = (*loc == 0) ? 1 : 0;
                return cycleCount;
        }
        break;
        case _6502_B_ZR_PAGE:
                offset = readMem(pc - 1);
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        s8 t = readMem(offset) >> 7;
        writeMem(offset,(readMem(offset) << 1) & 0xFE);
        writeMem(offset, readMem(offset) | status->C);
        status->C = t;
        status->N = (readMem(offset) >> 7);
        status->Z = (readMem(offset) == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_LSR_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM: {
                u8 *loc = &generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;

                status->C = *loc & 1;
                *loc = (*loc >> 1) & 0x7F;
                status->N = 0;
                status->Z = (*loc == 0) ? 1 : 0;

                return cycleCount;
        }
        break;
        case _6502_B_ZR_PAGE:
                offset = readMem(pc - 1);
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = ((generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF);
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = ((readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X]);
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        status->C = readMem(offset) & 1;
        writeMem(offset,(readMem(offset) >> 1) & 0x7F);
        status->N = 0;
        status->Z = (readMem(offset) == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_ROR_process(u8 a, u8 b, u8 c)
{

        int cycleCount = -1;
        u16 offset;
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];


        switch(b)
        {
        case _6502_B_ACCUM: {
                u8 *loc = &generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;

                s8 t = *loc & 1;
                *loc = (*loc >> 1) & 0x7F;
                *loc = *loc | (status->C ? 0x80 : 0x00);
                status->C = t;
                status->N = (*loc >> 7);
                status->Z = (*loc == 0) ? 1 : 0;
                return cycleCount;
        }
        break;
        case _6502_B_ZR_PAGE:
                offset = readMem(pc - 1);
                cycleCount = 5;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = ((generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF);
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8);
                cycleCount = 6;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = ((readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X]);
                cycleCount = 7;
        }
        break;
        default:
                return -1;
                break;
        }

        s8 t = readMem(offset) & 1;
        writeMem(offset,(readMem(offset) >> 1) & 0x7F);
        writeMem(offset, readMem(offset) | (status->C ? 0x80 : 0x00));
        status->C = t;
        status->N = (readMem(offset) >> 7);
        status->Z = (readMem(offset) == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_STX_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_B_ZR_PAGE:
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                //Special Case, Zero Page, Y
                offset = (generalPurposeRegisters[REGS_Y] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        writeMem(offset, generalPurposeRegisters[REGS_X]);

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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                //Special case, actually Zero Page, Y
                offset = (generalPurposeRegisters[REGS_Y] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_Y];
                cycleCount = 4;
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_X] = readMem(offset);
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        writeMem(offset, readMem(offset)- 1);
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = (readMem(offset) >> 7);
        status->Z = (readMem(offset) == 0) ? 1 : 0;

        return cycleCount;
}

int _6502_INC_process(u8 a, u8 b, u8 c)
{
        int cycleCount = -1;
        u16 offset;

        switch(b)
        {
        case _6502_B_ZR_PAGE:
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_B_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_B_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        writeMem(offset, readMem(offset)+1);
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = (readMem(offset) >> 7);
        status->Z = (readMem(offset) == 0) ? 1 : 0;

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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_C_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_ACCUM] & readMem(offset);

        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = (readMem(offset) >> 7) & 1;
        status->O = (readMem(offset) >> 6) & 1;
        status->Z = (t == 0);

        return cycleCount;
}

//Represents the indirect jump instruction
int _6502_JMP_process(u8 a, u8 b, u8 c)
{
        u16 targetA = readMem(pc - 2) | (readMem(pc - 1) << 8);
        u16 target = readMem(targetA) | (readMem(targetA + 1) << 8);
        pc = target;

        return 5; //cycleCount
}

//Represents the absolute jump instruction
int _6502_JMP_A_process(u8 a, u8 b, u8 c)
{
        u16 target = readMem(pc - 2) | (readMem(pc - 1) << 8);
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_C_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_C_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        writeMem(offset, generalPurposeRegisters[REGS_Y]);

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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_C_ZR_PAGE_X:
        {
                offset = (generalPurposeRegisters[REGS_X] + readMem(pc - 1)) & 0xFF;
                cycleCount = 4;
        }
        break;
        case _6502_C_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        case _6502_C_ABS_X:
        {
                offset = (readMem(pc - 2) | readMem(pc - 1) << 8) + generalPurposeRegisters[REGS_X];
                cycleCount = 4;
                //Check for page boundary
                if((offset & 0xFF00 ) < readMem(pc - 1) << 8) cycleCount++;
        }
        break;
        default:
                return -1;
                break;
        }

        generalPurposeRegisters[REGS_Y] = readMem(offset);
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_C_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_Y] - readMem(offset);
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = t >> 7;
        status->C = (generalPurposeRegisters[REGS_Y] >= readMem(offset));
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
                offset = readMem(pc - 1);
                cycleCount = 3;
                break;
        case _6502_C_ABS:
        {
                offset = readMem(pc - 2) | readMem(pc - 1) << 8;
                cycleCount = 4;
        }
        break;
        default:
                return -1;
                break;
        }

        u8 t = generalPurposeRegisters[REGS_X] - readMem(offset);
        _6502_STATUS *status = (_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS];
        status->N = t >> 7;
        status->C = (generalPurposeRegisters[REGS_X] >= readMem(offset));
        status->Z = (t == 0);

        return cycleCount;
}
