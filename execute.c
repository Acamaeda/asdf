/* execute.c
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the implementation file for the execute module.

 */

#include <stdlib.h>
#include "execute.h"
#include <stdio.h>
#include <assert.h>

const word NORMAL_OPS = 13;

typedef void (*normal_func)(word a, word b, word c, UM um);

void bad_op(word a, word b, word c, UM um)
{
        (void) a;
        (void) b;
        (void) c;
        (void) um;
        assert(0);
}

void move_op(word a, word b, word c, UM um)
{
        if (um->regs[c] != 0)
        {
                um->regs[a] = um->regs[b];
        }
}

void seg_load_op(word a, word b, word c, UM um)
{
        um->regs[a] = read_memory(um->regs[b], um->regs[c], um->mem);
}

void seg_store_op(word a, word b, word c, UM um)
{
        write_memory(um->regs[a], um->regs[b], um->regs[c], um->mem);
}

void add_op(word a, word b, word c, UM um)
{
        um->regs[a] = um->regs[b] + um->regs[c];
}

void mult_op(word a, word b, word c, UM um)
{
        um->regs[a] = um->regs[b] * um->regs[c];
}

void divide_op(word a, word b, word c, UM um)
{
        assert(um->regs[c] != 0);
        um->regs[a] = um->regs[b] / um->regs[c];
}

void nand_op(word a, word b, word c, UM um)
{
        um->regs[a] = ~(um->regs[b] & um->regs[c]);
}

void halt_op(word a, word b, word c, UM um)
{
        (void) a;
        (void) b;
        (void) c;
        free_UM(&um);
        exit(0);
}

void map_seg_op(word a, word b, word c, UM um)
{
        (void) a;
        um->regs[b] = new_seg(um->regs[c], um->mem);
}

void unmap_seg_op(word a, word b, word c, UM um)
{
        (void) a;
        (void) b;
        free_seg(um->regs[c], um->mem);
}

void output_op(word a, word b, word c, UM um)
{
        (void) a;
        (void) b;
        char val = um->regs[c];
        printf("%c", val);
}

void input_op(word a, word b, word c, UM um)
{
        (void) a;
        (void) b;
        um->regs[c] = getc(stdin);
}

void copy_seg_op(word a, word b, word c, UM um)
{
        (void) a;
        if (um->regs[b] != 0)
                copy_seg(um->regs[b], 0, um->mem);
        um->program_counter = um->regs[c];

}

const normal_func funcs[13] = {move_op, seg_load_op, seg_store_op, add_op,
                               mult_op, divide_op, nand_op, halt_op, map_seg_op,
                               unmap_seg_op, output_op, input_op, copy_seg_op};

void execute_operation(word op_id, word a, word b, word c, UM um)
{
        assert (op_id < NORMAL_OPS);
        funcs[op_id](a, b, c, um);
}

/* Load value */
void special_func(word reg, word val, UM um)
{
        um->regs[reg] = val;
}
