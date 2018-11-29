/* execute.h
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the header file for the Memory module.
 * Memory is an abstract data type for segmented memory.
 * New segments of different sizes can be created, deleted, and copied,
 * As well as read or written to.
 */

#ifndef EXECUTE_INCLUDED
#define EXECUTE_INCLUDED

#include "um_struct.h"

inline void execute_operation(word op_id, word a, word b, word c, UM um);

enum {SPECIAL_ID = 13};
/* Call this instead of funcs[SPECIAL_ID] */
inline void special_func(word reg, word val, UM um);

#endif
