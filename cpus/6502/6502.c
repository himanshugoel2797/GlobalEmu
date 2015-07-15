#include "6502.h"
#include "6502_cpuinfo.h"

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

int _6502_processSPECIAL(u8 inst);
int _6502_processTypeA(u8 a, u8 b, u8 c);
int _6502_processTypeB(u8 a, u8 b, u8 c);
int _6502_processTypeC(u8 a, u8 b, u8 c);

int _6502_processInstruction()
{
        u8 inst = memory[pc];

        u8 a = inst >> 5;
        u8 b = (inst << 3) >> 5;
        u8 c = (inst << 6) >> 6;

        int cycleCount = 1;

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

int _6502_processSPECIAL(u8 inst)
{
        int instructionLength = 1, cycleCount = 1;

        switch(inst)
        {
        case _6502_PHP:
                //Push the status register value onto the stack
                decrement_sp();
                *spLoc = generalPurposeRegisters[REGS_STATUS];
                cycleCount = 3;
                break;
        case _6502_PLP:
                //Pull the status register value from stack
                generalPurposeRegisters[REGS_STATUS] = *spLoc;
                increment_sp();
                cycleCount = 4;
                break;
        case _6502_PHA:
                //Push the accumulator value onto the stack
                decrement_sp();
                *spLoc = generalPurposeRegisters[REGS_ACCUM];
                cycleCount =3;
                break;
        case _6502_PLA:
                //Pull the accumulator value from stack
                generalPurposeRegisters[REGS_ACCUM] = *spLoc;
                increment_sp();
                cycleCount = 4;
                break;
        case _6502_DEY:
                //Decrement Y
                generalPurposeRegisters[REGS_Y]--;
                cycleCount = 2;
                break;
        case _6502_TAY:
                //Register Y = Accumulator
                generalPurposeRegisters[REGS_Y] = generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                break;
        case _6502_INY:
                //Increment Y
                generalPurposeRegisters[REGS_Y]++;
                cycleCount = 2;
                break;
        case _6502_INX:
                //Increment X
                generalPurposeRegisters[REGS_X]++;
                cycleCount = 2;
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
                break;
        case _6502_TXS:
                //SP = Register X
                sp = generalPurposeRegisters[REGS_X];
                cycleCount = 2;
                break;
        case _6502_TAX:
                //Register X = Accumulator
                generalPurposeRegisters[REGS_X] = generalPurposeRegisters[REGS_ACCUM];
                cycleCount = 2;
                break;
        case _6502_TSX:
                //Register X = SP
                generalPurposeRegisters[REGS_X] = sp;
                cycleCount = 2;
                break;
        case _6502_DEX:
                //Decrement X
                generalPurposeRegisters[REGS_X]--;
                cycleCount = 2;
                break;
        case _6502_NOP:
                //No Operation
                cycleCount = 2; //Do nothing for 2 cycles
                break;
        default:
                return -1;
        }

        pc += instructionLength;
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

        switch(a)
        {
        case _6502_ORA:
                break;
        case _6502_AND:
                break;
        case _6502_EOR:
                break;
        case _6502_ADC:
                break;
        case _6502_STA:
                break;
        case _6502_LDA:
                break;
        case _6502_CMP:
                break;
        case _6502_SBC:
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

        switch(a)
        {
        case _6502_ASL:
                break;
        case _6502_ROL:
                break;
        case _6502_LSR:
                break;
        case _6502_ROR:
                break;
        case _6502_STX:
                break;
        case _6502_LDX:
                break;
        case _6502_DEC:
                break;
        case _6502_INC:
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

        switch(a)
        {
        case _6502_BIT:
                break;
        case _6502_JMP:
                break;
        case _6502_JMP_A:
                break;
        case _6502_STY:
                break;
        case _6502_LDY:
                break;
        case _6502_CPY:
                break;
        case _6502_CPX:
                break;
        default:
                return -1;
        }

        return cycleCount;
}
