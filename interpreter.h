/* interpreter.h
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the header file for the Interpreter module.
 * It breaks down the instruction into its component values
 * and sends the result to the Execute module.
 */

#ifndef INTERPRETER_INCLUDED
#define INTERPRETER_INCLUDED

#include "execute.c"


inline void interpret(word instr, UM um);

#endif
