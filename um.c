/* um.c
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the main file for the UM. It initializes the UM, reads in the
 * program, and loops through the code.
 */

#include "interpreter.h"
#include <stdlib.h>
#include <stdio.h>
#include <except.h>
#include <assert.h>
FILE* open_file(int argc, char *argv[])
{
        /* If no file in the args, error*/
        if (argc == 1){
                /*if (!feof(stdin)){
                        process(stdin);
                }
                else{*/
                fprintf(stderr, "No file specified!\n");        
                exit(EXIT_FAILURE);
                        /* }*/
        }
		/* If there is a file specified in the args, open it*/
        else if(argc == 2){
                FILE *fp = fopen(argv[1], "r");
                if (fp == NULL) {
                        fprintf(stderr, "%s: %s %s %s\n",
                                argv[0], "Could not open file ",
                                argv[1], "for reading");
                        exit(EXIT_FAILURE);
                }
                return(fp);
        }
		/* Too many args, error */
        else{
                fprintf(stderr, "%s: improper syntax\n", argv[0]);
                exit(EXIT_FAILURE);
        }
        return NULL; /*Just here to make the compiler happy */
}

void read_program(FILE* fp, UM um)
{
        word i;
        word fsize;
        
        /* Find file length */
        fseek(fp, 0L, SEEK_END);
        fsize = ftell(fp) / sizeof(word);
        rewind(fp);

        new_seg(fsize, um->mem);
        for (i = 0; i < fsize; i++) {
                word instr;
                int j;
                char* ptr = (char*) &instr;
                for (j = 3; j >= 0; j--) {
                        int c = getc(fp);
                        *(ptr + j) = (char)c;
                }

                write_memory(0, i, instr, um->mem);
        }
}

void run_prog(UM um)
{
        
        int cycles = 0;
/* Main loop, ends with halt command */
        while (1) {
                word instr = read_memory(0, um->program_counter, um->mem);
             // if (instr != 0 || cycles < 5)
                    // fprintf(stderr, "\n%d %x\n", um->program_counter, instr);
                cycles++;
                um->program_counter++;
                interpret(instr, um);
        }
}

int main(int argc, char *argv[])
{
        FILE *fp = open_file(argc, argv);
        UM um = new_UM();
        TRY
                read_program(fp, um);
                fclose(fp);
        
                run_prog(um);
        EXCEPT(Assert_Failed)
                free(um);
                RERAISE;
                END_TRY;
}
