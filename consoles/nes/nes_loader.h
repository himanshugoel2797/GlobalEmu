#ifndef _NES_LOADER_H_
#define _NES_LOADER_H_

#include "nes.h"

//original iNES file header
typedef struct {
        u8 magic[4];
        u8 prg_rom_size; //In 16kb units
        u8 chr_rom_size; //In 8kb units
        u8 flags_6;
        u8 flags_7;
        u8 prg_ram_size; //In 8kb units
        u8 flags_9;
        u8 flags_10;
        u8 zero[5];
}iNES_ORIG;

#define GET_MIRROR_MODE(x) ( ((x->flags_6 & 0x0F) & 1) | (((x->flags_6 & 0x0F) >> 2) & 2))
#define GET_MAPPER_NUMBER(x) ( (((x->flags_6) & 0xF0) >> 4) | ((x->flags_7) & 0xF0))
#define HAS_BATTERY_BACKED_PRGRAM(x) (x->flags_6 & 2 == 2)
#define HAS_TRAINER(x) (x->flags_6 & 4 == 4)

typedef enum {
        HORIZONTAL_MIRRORING = 0,
        VERTICAL_MIRRORING = 1,
        FOUR_SCREEN_VRAM_A = 2,
        FOUR_SCREEN_VRAM_B = 3
}_NES_MIRROR_MODES;



#endif
