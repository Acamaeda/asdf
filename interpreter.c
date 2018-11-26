/* interpreter.c
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the implimentation  for the Interpreter module.
 *
 */

#include "interpreter.h"
#include <stdio.h>

/* Declared inline, we never call a shift of 64 so we don't need to check */
inline uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
        unsigned hi = lsb + width; /* one beyond the most significant bit */
        /* different type of right shift */
        return (word << (64 - hi)) >> (64 - width);
}

void interpret(word instr, UM um)
{
        word op = (word)Bitpack_getu((uint64_t)instr, 4, 28);
        if (op == SPECIAL_ID){
                word a = (word)Bitpack_getu((uint64_t)instr, 3, 25);
                word val = (word)Bitpack_getu((uint64_t)instr, 25, 0);
                special_func(a, val, um);
        }
        else
        {
                word c = (word)Bitpack_getu((uint64_t)instr, 3, 0);
                word b = (word)Bitpack_getu((uint64_t)instr, 3, 3);
                word a = (word)Bitpack_getu((uint64_t)instr, 3, 6);
                execute_operation(op, a, b, c, um);
        }
        (void)um;
}

