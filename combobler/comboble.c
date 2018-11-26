/* compile.c
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is a basic compiler thing. It's probably super buggy and bad.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <seq.h>
#include "bitpack.h"
#include <string.h>

typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */

Um_instruction make(Um_opcode op, int rc, int rb, int ra)
{
        uint64_t word = 0;
        fprintf(stderr, "%x ", op);
        assert ((unsigned)op <= 13);
        assert ((unsigned)ra <= 7);
        assert ((unsigned)rb <= 7);
        assert ((unsigned)rc <= 7);

        word = Bitpack_newu(word, 4, 28, (uint64_t) op);
        word = Bitpack_newu(word, 3, 0,  (uint64_t) rc);
        word = Bitpack_newu(word, 3, 3,  (uint64_t) rb);
        word = Bitpack_newu(word, 3, 6,  (uint64_t) ra);
        return (Um_instruction) word;
}

Um_instruction loaddval(unsigned ra, unsigned val)
{
        uint64_t word = 0;
        Um_opcode op = LV;
        assert (Bitpack_fitsu(val, 25));
        assert ((unsigned)ra <= 7);

        word = Bitpack_newu(word, 4, 28, (uint64_t) op);
        word = Bitpack_newu(word, 3, 25, (uint64_t) ra);
        word = Bitpack_newu(word, 25, 0, (uint64_t) val);

        return (Um_instruction) word;
}

extern void Um_write_instr(FILE *output, Um_instruction inst)
{
        int i;
        char *ptr = (char*) &inst;
        for (i = 3; i >= 0; i--) {
                fprintf(output, "%c", *(ptr + i));
        }    
}

Um_instruction next(FILE *in)
{
        Um_instruction a;
        fscanf(in, "%u", &a);
        fprintf(stderr, " %x", a);

        return a;
}

void skip_line(FILE *in)
{
        char c = 'a';
        while ((c = fgetc(in)) != '\n'){
                fprintf(stderr, "%c", c);
        }
                
}

void compile(FILE *in, FILE *out)
{
        char instr[32];
        int write = 0;
        int line = 0;//for debugging
        while (fscanf(in, "%31s", instr) != EOF){
                fprintf(stderr, "\n%d: %s", line, instr);

                Um_instruction word = 0;
                write = 1;
                /* Set ra to $val */
                if (strcmp(instr, "loadv") == 0){
                        Um_instruction a = next(in);
                        Um_instruction val = next(in);
                        word = loaddval(a, val);
                }
                
                /* Set ra to rb if c != 0 */
                else if ((strcmp(instr, "if") == 0) || 
                         (strcmp(instr, "move") == 0)) {
                        word = make(0, next(in), next(in), next(in));
                }

                else if (strcmp(instr, "loads") == 0){
                        word = make(1, next(in), next(in), next(in));
                }
                else if (strcmp(instr, "store") == 0){
                        word = make(2, next(in), next(in), next(in));
                }
                else if (strcmp(instr, "add") == 0){
                        word = make(3, next(in), next(in), next(in));
                }
                else if (strcmp(instr, "mult") == 0){
                        word = make(4, next(in), next(in), next(in));
                }
                else if (strcmp(instr, "divide") == 0){
                        word = make(5, next(in), next(in), next(in));
                }
                else if (strcmp(instr, "nand") == 0){
                        word = make(6, next(in), next(in), next(in));
                }
                else if (strcmp(instr, "halt") == 0){
                        word = make(7, 0, 0, 0);
                }
                else if (strcmp(instr, "map") == 0){
                        word = make(8, next(in), next(in), 0);
                }
                else if (strcmp(instr, "unmap") == 0){
                        word = make(9, next(in), 0, 0);
                }
                else if (strcmp(instr, "out") == 0){
                        word = make(10, next(in), 0, 0);
                }
                else if (strcmp(instr, "in") == 0){
                        word = make(11, next(in), 0, 0);
                }
                else if (strcmp(instr, "jump") == 0){
                        word = make(12, next(in), next(in), 0);
                }
                else if (strcmp(instr, "//") == 0){
                        skip_line(in);
                        write = 0;
                }
                else{
                        fprintf(stderr, "%s is not a command", instr);
                        exit(1);
                }

                if (write == 1)
                        Um_write_instr(out, word);

                line++;
        }
                fprintf(stderr, "\n");

}

int main(int argc, char *argv[])
{
        FILE *in;
        FILE *out;
		/* If there is a file specified in the args, open it*/

        if(argc == 3){
                in = fopen(argv[1], "r");
                if (in == NULL) {
                        fprintf(stderr, "%s: %s %s %s\n",
                                argv[0], "Could not open file ",
                                argv[1], "for reading");
                        exit(EXIT_FAILURE);
                }

                out = fopen(argv[2], "w");
                compile(in, out);
        }
		/* Too many args, error */
        else{
                fprintf(stderr, "%s: improper syntax\n", argv[0]);
                exit(EXIT_FAILURE);
        }
        return 0; /*Just here to make the compiler happy */
}
