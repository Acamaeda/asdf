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

typedef struct Memory *Memory;
typedef  uint32_t word;

/* Returns 1 if there is a segment for a given id, or 0 otherwise */
word valid_addr(word seg, word addr, Memory mem);

word read_memory(word seg, word addr, Memory mem);
void write_memory(word seg, word addr, word value, Memory mem);

void copy_seg(word src, word dest, Memory mem);

/* Adds a new segment at an available segment id, and returns its id */
word new_seg(word size, Memory mem);
/* Frees a segment from memory, opening its id for future use. */
void free_seg(word seg, Memory mem);

Memory new_memory();
void free_memory(Memory *mem);
#endif
