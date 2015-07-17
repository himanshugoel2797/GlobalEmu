#ifndef _NES_PPU_H_
#define _NES_PPU_H_

#include "../../common.h"
#include "nes.h"
#include "../../cpus/6502/6502.h"

typedef struct {
        union {
                u8 val;
                struct {
                        u8 NMI_enable : 1;
                        u8 PPU_M_S : 1;
                        u8 sprite_h : 1;
                        u8 bg_tile_addr : 1;
                        u8 sprite_tile_addr : 1;
                        u8 inc_mode : 1;
                        u8 nametable_select : 1;
                }b;
        }PPUCTRL;
        union {
                u8 val;
                struct {
                        u8 color_emphasis : 3;
                        u8 sprite_enable : 1;
                        u8 bg_enable : 1;
                        u8 sprite_left_col_enable : 1;
                        u8 bg_left_col_enable : 1;
                        u8 greyscale : 1;
                }b;
        }PPUMASK;

        union {
                u8 val;
                struct {
                        u8 vblank : 1;
                        u8 sprite_0_hit : 1;
                        u8 sprite_overflow : 1;
                }b;
        }PPUSTATUS; //Read resets write pair for PPUSCROLL, PPUADDR

        u8 OAMADDR;
        u8 OAMDATA;
        u8 PPSCROLL;
        u8 PPUADDR;
        u8 PPUDATA;
        u8 OAMDMA;
} PPU_REGISTER_FILE;

#define PPU_REGISTER_LOC 0x2000
extern PPU_REGISTER_FILE *ppu_regs;

///Initialize the PPU
int ppu_initialize();

#endif
