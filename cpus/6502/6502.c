#include "6502.h"
#include "6502_cpuinfo.h"

//6502 memory
u8 *memory;

//6502 Register file
u8 generalPurposeRegisters[4];
u8 sp;
u8 *spLoc;
u16 pc;


int _6502_initialize(size_t memorySize)
{
        //Allocate memory for the RAM
        memory = malloc(memorySize * sizeof(u8));
        memset(memory, 0, memorySize * sizeof(u8));

        //Initialize registers
        generalPurposeRegisters[ACCUM] = 0;
        generalPurposeRegisters[X] = 0;
        generalPurposeRegisters[Y] = 0;
        generalPurposeRegisters[STATUS] = 1 << STATUS_UNUSED; //Everything but STATUS_UNUSED is zero

        sp = SOFT_SP_START;
        spLoc = (memory + REAL_SP_START);

        return 0;
}

u8* _6502_getMemory(){
        return memory;
}

int _6502_processInstruction()
{
        u8 inst = memory[pc];

        u8 a = inst >> 5;
        u8 b = (inst << 3) >> 5;
        u8 c = (inst << 6) >> 6;

        int instructionLength = 0;

        switch(c)
        {
        case A:
                //Determine the length of the instruction based on the addressing mode
                if(b == _6502_A_ABS || b == _6502_A_ABS_X || b == _6502_A_ABS_Y) instructionLength = 3;


                break;
        case B:
                //Determine the length of the instruction based on the addressing mode
                if(b == _6502_B_ABS || b == _6502_B_ABS_X) instructionLength = 3;


                break;
        case C:
                //Determine the length of the instruction based on the addressing mode
                if(b == _6502_B_ABS || b == _6502_B_ABS_X) instructionLength = 3;


                break;
        }

        return 0;
}
