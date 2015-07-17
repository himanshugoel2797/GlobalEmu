#include "nes.h"
#include "nes_loader.h"
#include "nes_memory.h"


int nes_loadProgram(u8 *prog, size_t len)
{
        memcpy(getMemory(), prog, len);
        return 0;
}


int nes_load_OLDiNES(u8* data, size_t len);
int nes_load_iNES2(u8* data, size_t len);
int nes_load_iNES(const char *filename)
{
        FILE *fd = fopen(filename, "rb");
        if(fd < 0) return -1;
        fseek(fd, 0, SEEK_END);
        size_t len = ftell(fd);
        fseek(fd, 0, SEEK_SET);

        u8 *buffer = malloc(sizeof(u8) * len);
        fread(buffer, 1, len, fd);
        fclose(fd);

        iNES_ORIG *origHDR = (iNES_ORIG*)buffer;

        //Check the header
        if(origHDR->magic[0] != 0x4E | origHDR->magic[1] != 0x45
           | origHDR->magic[2] != 0x53 | origHDR->magic[3] != 0x1A) return -1;

        //Make sure this is the older format
        for(int i = 0; i < 5; i++)
                if(origHDR->zero[i] != 0) {
                        origHDR = NULL;
                        break;
                }

        //If origHDR is NULL this isn't the older format
        if(origHDR == NULL) return nes_load_iNES2(buffer, len); //TODO Implement NES 2.0
        else return nes_load_OLDiNES(buffer, len);
}


int nes_load_OLDiNES(u8* data, size_t len){

        iNES_ORIG *hdr = (iNES_ORIG*)data;
        int offset = sizeof(iNES_ORIG);
        u8 *prgROM, *chrROM;

        config.persistent_PRGRAM = HAS_BATTERY_BACKED_PRGRAM(hdr);
        config.mirror_mode = GET_MIRROR_MODE(hdr);

        //Due to certain crap, only the lower 4 bits are reliable
        config.mapperNumber = GET_MAPPER_NUMBER(hdr) & 0x0F;

        if(HAS_TRAINER(hdr))
        {
              //TODO load in the trainer somewhere
              offset += 512;  //Move to the next part
        }

        prgROM = data + offset;
        offset += hdr->prg_rom_size * 16384;

        if(hdr->chr_rom_size != 0)
        {
          chrROM = data + offset;
          offset += hdr->chr_rom_size * 8192;
        }

        //Place data into the appropriate places

        return 0;
}

int nes_load_iNES2(u8* data, size_t len){
        return -2;
}
