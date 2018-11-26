/* interpreter.c
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the implimentation  for the Interpreter module.
 *
 */

#include "bitpack.h"
#include "interpreter.h"
#include <stdio.h>

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

