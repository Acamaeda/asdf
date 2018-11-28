/* memory.h
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the header file for the Memory module.
 * Memory is an abstract data type for segmented memory.
 * New segments of different sizes can be created, deleted, and copied,
 * As well as read or written to.
 */

#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED

#include <stdint.h>
#include <uarray.h>
#include <seq.h>

typedef  uint32_t word;

/* Not secret so current seg can be stored */
struct Memory{
        UArray_T segs;
        Seq_T free_ids;
        word next_id;
};

typedef struct Segment{
        word size;
        word *array;
} *Segment;

typedef struct Memory *Memory;

/* Returns 1 if there is a segment for a given id, or 0 otherwise */
word valid_addr(word seg, word addr, Memory mem);

word read_memory(word seg, word addr, Memory mem);
void write_memory(word seg, word addr, word value, Memory mem);

/* Does not do one checks, be careful with this! */
word read_prog_memory(word seg, word addr, Memory mem);


void copy_seg(word src, word dest, Memory mem);

/* Adds a new segment at an available segment id, and returns its id */
word new_seg(word size, Memory mem);
/* Frees a segment from memory, opening its id for future use. */
void free_seg(word seg, Memory mem);

Memory new_memory();
void free_memory(Memory *mem);
#endif
