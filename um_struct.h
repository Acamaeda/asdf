/* um_struct.h
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the header file for the UM struct.
 * It contains all of the essential information for the UM and will be passed
 * around to most modules. It isn't secret because other things need to use it.
 */

#ifndef UM_STRUCT_INCLUDED
#define UM_STRUCT_INCLUDED

#include <stdint.h>
#include "memory.c"

typedef struct UM{
        Memory mem;
        word *regs;
        word program_counter;
        word * code;
        word code_length;
}*UM;

UM new_UM();
void free_UM(UM *um);

word valid_reg(word reg);
#endif
