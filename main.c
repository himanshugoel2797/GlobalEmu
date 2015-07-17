#include "common.h"

#include "consoles/nes/nes.h"
#include "cpus/6502/6502.h"

int main(int argc, char *argv[])
{
        nes_initialize();

        u8 testProg[0x10000] = {0xE8};

        if(argc > 1)
        {
                FILE *fd = fopen(argv[1], "rb");
                if(fd >= 0) {
                        fseek(fd, 0, SEEK_END);
                        int len = ftell(fd);
                        fseek(fd, 0, SEEK_SET);
                        fread(testProg, 1, len, fd);
                }
        }else{

                for(u16 i = 1; i <= 0xFFFF; i++)
                {
                        testProg[i] = 0xEA;
                }
                testProg[(u16)-2] = 0xE8;
        }

        nes_loadProgram(testProg, 0x10000);

        //_6502_setRegister(3, 0);
        _6502_setPC(0x400);

        int cont = 1;
        u16 prevPC = 0;

        while(cont)
        {
                u16 pc = _6502_getPC();

                if(prevPC == pc)cont = 0;
                if(nes_processInstruction() < 0) cont = 0;
                printf("A: 0x%02x X: 0x%02x Y: 0x%02x S: 0x%02x SP: 0x%02x PC: 0x%04x\r",
                       _6502_getRegister(0), _6502_getRegister(1),_6502_getRegister(2),
                       _6502_getRegister(3), _6502_getSP(), pc);
                prevPC = pc;
        }

        return 0;
}
