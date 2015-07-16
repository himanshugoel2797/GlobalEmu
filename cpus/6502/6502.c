#include "6502.h"
#include "6502_cpuinfo.h"
#include "6502_instr.h"

//6502 memory
u8 *memory;

//6502 Register file
u8 generalPurposeRegisters[4];
u8 sp;
u8 *spLoc;
u16 pc;

inline void decrement_sp()
{
        sp--;
        spLoc--;
        if(spLoc < memory + REAL_SP_END) spLoc = memory + REAL_SP_START;
}

inline void increment_sp()
{
        sp++;
        spLoc++;
        if(spLoc > memory + REAL_SP_START) spLoc = memory + REAL_SP_END;
}


int _6502_initialize(size_t memorySize)
{
        //Allocate memory for the RAM
        memory = malloc(memorySize * sizeof(u8));
        memset(memory, 0xFF, memorySize * sizeof(u8));

        //Initialize registers
        generalPurposeRegisters[REGS_ACCUM] = 0;
        generalPurposeRegisters[REGS_X] = 0;
        generalPurposeRegisters[REGS_Y] = 0;
        generalPurposeRegisters[REGS_STATUS] = ~(1 << STATUS_INT); //Interrupts disabled

        sp = 0xFD;
        spLoc = (memory + 0x1FD);

        return 0;
}

u8* _6502_getMemory(){
        return memory;
}

u8 _6502_getRegister(int reg)
{
        return generalPurposeRegisters[reg];
}

int _6502_setRegister(int reg, u8 val)
{
        generalPurposeRegisters[reg] = val;
        return val;
}

u16 _6502_getPC(){
        return pc;
}

int _6502_setPC(u16 val)
{
        pc = val;
        return pc;
}

u16 _6502_getSP(){
        return sp;
}

int _6502_setSP(u16 val)
{
        spLoc = memory + val;
        sp = val & 0xFF;
        return sp;
}


int _6502_processSPECIAL(u8 inst);
int _6502_processCONDITIONAL(u8 inst);
int _6502_processTypeA(u8 a, u8 b, u8 c);
int _6502_processTypeB(u8 a, u8 b, u8 c);
int _6502_processTypeC(u8 a, u8 b, u8 c);

int _6502_processInstruction()
{
        if(pc == 0xffff) return -1;
        u8 inst = memory[pc];


        u8 a = inst >> 5;
        u8 b = (inst >> 2) & 7;
        u8 c = inst & 3;

        int cycleCount = 1;

        if(_6502_isCONDITIONAL(inst))
                return _6502_processCONDITIONAL(inst);

        if(_6502_isSPECIAL(inst))
                return _6502_processSPECIAL(inst);

        switch(c)
        {
        case A:
                cycleCount = _6502_processTypeA(a, b, c);
                break;
        case B:
                cycleCount = _6502_processTypeB(a, b, c);
                break;
        case C:
                cycleCount = _6502_processTypeC(a, b, c);
                break;
        default:
                return -1;
        }

        return cycleCount;
}

int _6502_processCONDITIONAL(u8 inst)
{
        int cycleCount = 2; //Add 1 if branch to same page, 2 if branch to different page
        pc += 2;

        u8 flag = inst >> 6;
        u8 cmpVal = (inst & 32) >> 5;
        u8 valToCheck = 0;


        switch(flag)
        {
        case _6502_COND_OP_N:
                valToCheck = ((_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS])->N;
                break;
        case _6502_COND_OP_O:
                valToCheck = ((_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS])->O;
                break;
        case _6502_COND_OP_C:
                valToCheck = ((_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS])->C;
                break;
        case _6502_COND_OP_Z:
                valToCheck = ((_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS])->Z;
                break;
        default:
                return -1;
        }

        if(valToCheck == cmpVal)
        {
                cycleCount++;
                if((pc & 0xFF00) < ((pc + (s8)memory[pc - 1]) & 0xFF00)) cycleCount++;
                printf("\nInst: %04x, PC: %08x, %08x\n", inst, pc, (s8)memory[pc - 1]);
                pc += (s8)memory[pc - 1];
        }

        return cycleCount;
}

int _6502_processSPECIAL(u8 inst)
{
        int cycleCount = -1;
        pc++;

        switch(inst)
        {
        case _6502_PHP:
                //Push the status register value onto the stack
                *spLoc = generalPurposeRegisters[REGS_STATUS] | (3 << 4);
                decrement_sp();
                cycleCount = 3;
                break;
        case _6502_PLP:
                //Pull the status register value from stack
                increment_sp();
                generalPurposeRegisters[REGS_STATUS] = *spLoc;
                cycleCount = 4;
                break;
        case _6502_PHA:
                //Push the accumulator value onto the stack
                *spLoc = generalPurposeRegisters[REGS_ACCUM];
                decrement_sp();
                cycleCount =3;
                break;
        case _6502_PLA:
                //Pull the accumulator value from stack
                increment_sp();
                generalPurposeRegisters[REGS_ACCUM] = *spLoc;
                cycleCount = 4;
                _6502_storeNZ(REGS_ACCUM);
                break;
        case _6502_DEY:
                //Decrement Y
                generalPurposeRegisters[REGS_Y]--;
                cycleCount = 2;
                _6502_storeNZ(REGS_Y);
                break;
        case _6502_TAY:
                //Register Y = Accumulator
                generalPurposeRegisters[REGS_Y] = generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                _6502_storeNZ(REGS_Y);
                break;
        case _6502_INY:
                //Increment Y
                generalPurposeRegisters[REGS_Y]++;
                cycleCount = 2;
                _6502_storeNZ(REGS_Y);
                break;
        case _6502_INX:
                //Increment X
                generalPurposeRegisters[REGS_X]++;
                cycleCount = 2;
                _6502_storeNZ(REGS_X);
                break;
        case _6502_CLC:
                //Clear carry bit
                generalPurposeRegisters[REGS_STATUS] &= ~(1 << STATUS_CARRY);
                cycleCount = 2;
                break;
        case _6502_SEC:
                //Set carry bit
                generalPurposeRegisters[REGS_STATUS] |= (1 << STATUS_CARRY);
                cycleCount = 2;
                break;
        case _6502_CLI:
                //Enable interrupts
                generalPurposeRegisters[REGS_STATUS] &= ~(1 << STATUS_INT);
                cycleCount = 2;
                break;
        case _6502_SEI:
                //Disable interrupts
                generalPurposeRegisters[REGS_STATUS] |= (1 << STATUS_INT);
                cycleCount = 2;
                break;
        case _6502_TYA:
                //Accumulator = Register Y
                generalPurposeRegisters[REGS_ACCUM] = generalPurposeRegisters[REGS_Y];
                cycleCount = 2;
                _6502_storeNZ(REGS_ACCUM);
                break;
        case _6502_CLV:
                //Clear overflow bit
                generalPurposeRegisters[REGS_STATUS] &= ~(1 << STATUS_OVRF);
                cycleCount = 2;
                break;
        case _6502_CLD:
                //Clear decimal mode bit (Not on NES)
                generalPurposeRegisters[REGS_STATUS] &= ~(1 << STATUS_DEC);
                cycleCount = 2;
                break;
        case _6502_SED:
                //Set decimal mode bit (Not on NES)
                generalPurposeRegisters[REGS_STATUS] |= (1 << STATUS_DEC);
                cycleCount = 2;
                break;
        case _6502_TXA:
                //Accumulator = Register X
                generalPurposeRegisters[REGS_ACCUM] = generalPurposeRegisters[REGS_X];
                cycleCount = 2;
                _6502_storeNZ(REGS_ACCUM);
                break;
        case _6502_TXS:
                //SP = Register X
                sp = generalPurposeRegisters[REGS_X];
                spLoc = memory + 0x0100 + sp;
                cycleCount = 2;
                break;
        case _6502_TAX:
                //Register X = Accumulator
                generalPurposeRegisters[REGS_X] = generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                _6502_storeNZ(REGS_X);
                break;
        case _6502_TSX:
                //Register X = SP
                generalPurposeRegisters[REGS_X] = sp;
                cycleCount = 2;
                _6502_storeNZ(REGS_X);
                break;
        case _6502_DEX:
                //Decrement X
                generalPurposeRegisters[REGS_X]--;
                cycleCount = 2;
                _6502_storeNZ(REGS_X);
                break;
        case _6502_NOP:
                //No Operation
                cycleCount = 2; //Do nothing for 2 cycles
                break;
        case _6502_JSR:
                pc+=2;
                u16 loc = memory[pc - 2] | (memory[pc - 1] << 8);
                *spLoc = ((pc - 1) & 0xFF00) >> 8;
                decrement_sp();
                *spLoc = (pc - 1) & 0x00FF;
                decrement_sp();
                pc = loc;
                cycleCount = 6;
                break;
        case _6502_BRK:
                pc++;
                *spLoc = (pc & 0xFF00) >> 8;
                decrement_sp();
                *spLoc = (pc & 0x00FF);
                decrement_sp();
                *spLoc = generalPurposeRegisters[REGS_STATUS] | (3 << 4); //Enable both unused bits
                ((_6502_STATUS*)&generalPurposeRegisters[REGS_STATUS])->I = 1;  //Disable interrupts
                decrement_sp();
                pc = memory[0xFFFE] | ( ((u16)memory[0xFFFF]) << 8);
                cycleCount = 7;
                break;
        case _6502_RTI:
                //TODO implement RTI
                increment_sp();
                generalPurposeRegisters[REGS_STATUS] = *spLoc;
                increment_sp();
                pc = *spLoc;
                increment_sp();
                pc |= (*spLoc << 8);
                cycleCount = 6;
                break;
        case _6502_RTS:
                increment_sp();
                u8 l = *spLoc;
                increment_sp();
                u8 h = *spLoc;
                pc = (((u16)h << 8) | l) + 1;
                cycleCount = 6;
                break;
        default:
                return -1;
        }

        return cycleCount;
}

int _6502_processTypeA(u8 a, u8 b, u8 c)
{
        int instructionLength = 0, cycleCount = 1;
        //Determine the length of the instruction based on the addressing mode
        if(b == _6502_A_ABS || b == _6502_A_ABS_X || b == _6502_A_ABS_Y) instructionLength = 3;
        else if(b == _6502_A_ZR_PAGE || b == _6502_A_IMM ||
                b == _6502_A_ZR_PAGE_IND_X || b == _6502_A_ZR_PAGE_IND_Y ||
                b == _6502_A_ZR_PAGE_X) instructionLength = 2;

        pc += instructionLength;

        switch(a)
        {
        case _6502_ORA:
                cycleCount = _6502_ORA_process(a, b, c);
                break;
        case _6502_AND:
                cycleCount = _6502_AND_process(a, b, c);
                break;
        case _6502_EOR:
                cycleCount = _6502_EOR_process(a, b, c);
                break;
        case _6502_ADC:
                cycleCount = _6502_ADC_process(a, b, c);
                break;
        case _6502_STA:
                cycleCount = _6502_STA_process(a, b, c);
                break;
        case _6502_LDA:
                cycleCount = _6502_LDA_process(a, b, c);
                break;
        case _6502_CMP:
                cycleCount = _6502_CMP_process(a, b, c);
                break;
        case _6502_SBC:
                cycleCount = _6502_SBC_process(a, b, c);
                break;
        default:
                return -1;
        }

        return cycleCount;
}

int _6502_processTypeB(u8 a, u8 b, u8 c)
{
        int instructionLength  = 0, cycleCount = 0;
        //Determine the length of the instruction based on the addressing mode
        if(b == _6502_B_ABS || b == _6502_B_ABS_X) instructionLength = 3;
        else if(b == _6502_B_ZR_PAGE || b == _6502_B_IMM ||
                b == _6502_B_ZR_PAGE_X) instructionLength = 2;
        else if(b == _6502_B_ACCUM) instructionLength = 1;

        pc += instructionLength;

        switch(a)
        {
        case _6502_ASL:
                cycleCount = _6502_ASL_process(a, b, c);
                break;
        case _6502_ROL:
                cycleCount = _6502_ROL_process(a, b, c);
                break;
        case _6502_LSR:
                cycleCount = _6502_LSR_process(a, b, c);
                break;
        case _6502_ROR:
                cycleCount = _6502_ROR_process(a, b, c);
                break;
        case _6502_STX:
                cycleCount = _6502_STX_process(a, b, c);
                break;
        case _6502_LDX:
                cycleCount = _6502_LDX_process(a, b, c);
                break;
        case _6502_DEC:
                cycleCount = _6502_DEC_process(a, b, c);
                break;
        case _6502_INC:
                cycleCount = _6502_INC_process(a, b, c);
                break;
        default:
                return -1;
        }

        return cycleCount;
}

int _6502_processTypeC(u8 a, u8 b, u8 c)
{
        int instructionLength = 0, cycleCount = 0;
        //Determine the length of the instruction based on the addressing mode
        if(b == _6502_C_ABS || b == _6502_C_ABS_X) instructionLength = 3;
        else if(b == _6502_C_ZR_PAGE || b == _6502_C_IMM ||
                b == _6502_C_ZR_PAGE_X) instructionLength = 2;

        pc += instructionLength;

        switch(a)
        {
        case _6502_BIT:
                cycleCount = _6502_BIT_process(a, b, c);
                break;
        case _6502_JMP:
                cycleCount = _6502_JMP_process(a, b, c);
                break;
        case _6502_JMP_A:
                cycleCount = _6502_JMP_A_process(a, b, c);
                break;
        case _6502_STY:
                cycleCount = _6502_STY_process(a, b, c);
                break;
        case _6502_LDY:
                cycleCount = _6502_LDY_process(a, b, c);
                break;
        case _6502_CPY:
                cycleCount = _6502_CPY_process(a, b, c);
                break;
        case _6502_CPX:
                cycleCount = _6502_CPX_process(a, b, c);
                break;
        default:
                return -1;
        }

        return cycleCount;
}
