#include "endian.h"

Endianness tools_determineSystemEndian()
{
        char tmp[4] = {0x1, 0x2, 0x3, 0x4};
        if(*((int*)tmp) == 0x01020304) return BIG_ENDIAN;
        else if(*((int*)tmp) == 0x04030201) return LITTLE_ENDIAN;

        return UNKNOWN_ENDIAN;
}

int tools_endian_memcpy(void *src, void *dest, size_t len, Endianness targetEndian)
{
        if(targetEndian == tools_determineSystemEndian()) //If the endiannness is the same, just memcpy
        {
                memcpy(src, dest, len);
                return 0;
        }

        printf("Implement Endian Independant memcpy! [endian.c]");
        return -1;
}

inline int tools_getBit(int num, int bit, int bitCount, Endianness targetEndian)
{
        if(tools_determineSystemEndian() == targetEndian && bitCount > 8)
        {
                return (num >> bit) & 1;
        }else{
                return (num >> (bitCount - bit - 1)) & 1;
        }
}

inline int tools_setBit(int num, int bit, int bitCount, Endianness targetEndian)
{
        if(tools_determineSystemEndian() != targetEndian && bitCount > 8)
        {
                return num | (1 << (bitCount - bit - 1));
        }else{
                return num | (1 << bit);
        }
}

inline int tools_clearBit(int num, int bit, int bitCount, Endianness targetEndian)
{
        if(tools_determineSystemEndian() != targetEndian && bitCount > 8)
        {
                return num & ~(1 << (bitCount - bit - 1));
        }else{
                return num & ~(1 << bit);
        }
}

inline int tools_toggleBit(int num, int bit, int bitCount, Endianness targetEndian)
{
        if(tools_determineSystemEndian() != targetEndian && bitCount > 8)
        {
                return num ^ (1 << (bitCount - bit - 1));
        }else{
                return num ^ (1 << bit);
        }
}
