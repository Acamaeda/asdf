/* um_struct.c
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the implementation file for the UM struct.
 */

#include "um_struct.h"
#include <stdlib.h>

const word REG_NUM = 8;

UM new_UM()
{
        UM um = malloc(sizeof(struct UM));
        um->regs = calloc(REG_NUM, sizeof(word));
        um->mem = new_memory();
        um->program_counter = 0;
        return um;
}

void free_UM(UM *ump)
{
        UM um = *ump;
        free_memory(&(um->mem));
        free(um->regs);
        free(um);
}

word valid_reg(word reg)
{
        return (reg < REG_NUM);
}
