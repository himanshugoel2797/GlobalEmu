#ifndef _TOOLS_ENDIAN_H_
#define _TOOLS_ENDIAN_H_

#include "../common.h"

typedef enum {
        UNKNOWN_ENDIAN = 0,
        LITTLE_ENDIAN = 1,
        BIG_ENDIAN = 2
} Endianness;

Endianness tools_determineSystemEndian();
int tools_endian_memcpy(void *src, void *dest, size_t len, Endianness targetEndian);

extern inline int tools_getBit(int num, int bit, int bitCount, Endianness targetEndian);
extern inline int tools_setBit(int num, int bit, int bitCount, Endianness targetEndian);
extern inline int tools_clearBit(int num, int bit, int bitCount, Endianness targetEndian);
extern inline int tools_toggleBit(int num, int bit, int bitCount, Endianness targetEndian);

#endif
