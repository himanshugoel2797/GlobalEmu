#ifndef _NES_APU_H_
#define _NES_APU_H_
#include "../../common.h"

typedef struct {
        struct {
                //$4000
                u8 duty : 2;
                u8 env_loop : 1;
                u8 const_vol : 1;
                u8 vol_env : 4;

                //$4001
                u8 sweep_enabled : 1;
                u8 sweep_period : 3;
                u8 sweep_negate : 1;
                u8 sweep_shift : 3;

                //$4002
                u8 timer_low : 8;

                //$4003
                u8 len_counter_load : 5;
                u8 timer_high : 3;
        }PULSE_1;

        struct {
                //$4004
                u8 duty : 2;
                u8 env_loop : 1;
                u8 const_vol : 1;
                u8 vol_env : 4;

                //$4005
                u8 sweep_enabled : 1;
                u8 sweep_period : 3;
                u8 sweep_negate : 1;
                u8 sweep_shift : 3;

                //$4006
                u8 timer_low : 8;

                //$4007
                u8 len_counter_load : 5;
                u8 timer_high : 3;
        }PULSE_2;

        struct {
                //$4008
                u8 linear_counter_ctrl  : 1;
                u8 linear_counter_load : 7;

                //$4009
                u8 unused0 : 8;

                //$400A
                u8 timer_low : 8;

                //$400B
                u8 len_counter_load : 5;
                u8 timer_high : 3;
        }TRIANGLE;

        struct {
                //$400C
                u8 unused0 : 2;
                u8 len_counter_halt : 1;
                u8 const_vol : 1;
                u8 vol_env : 4;

                //$400D
                u8 unused1 : 8;

                //$400E
                u8 loop_noise : 1;
                u8 unused2 : 3;
                u8 noise_period : 4;

                //$400F
                u8 len_counter_load : 5;
                u8 unused3 : 3;
        }NOISE;
        struct {
                //$4010
                u8 irq_enable : 1;
                u8 loop : 1;
                u8 unused0 : 2;
                u8 frequency : 4;

                //$4011
                u8 unused1 : 1;
                u8 load_counter : 7;

                //$4012
                u8 sample_addr : 8;

                //$4013
                u8 sample_len : 8;
        }DMC;

        u8 unused0;
        union {
                //$4015
                u8 dmc_intrpt : 1;
                u8 frame_intrpt : 1;
                u8 unused0 : 1;
                u8 dmc_active : 1;
                u8 nt21 : 4;
        } CHNL_ENABLE;

        u8 unused1;
        union {
                //$4017
                u8 mode : 1;
                u8 irq_inhibit : 1;
                u8 unused0 : 6;
        } FRAME_COUNTER;
}APU_REGISTER_FILE;

#define APU_REGISTER_OFFSET 0x4000
extern APU_REGISTER_FILE *apu_regs;

///Initialize APU
int apu_initialize();

#endif /* end of include guard: _NES_APU_H_ */
