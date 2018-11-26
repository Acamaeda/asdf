/* memtests.h
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * Assorted tests for the Memory module
 */

#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

void basic_test()
{
        printf("Performing basic test\n");
        Memory m = new_memory();
        int id = new_seg(10, m);
        int success = 1;
        for (int i = 0; i < 10; i++)
                write_memory(id, i, i, m);
        for (int i = 0; i < 10; i++) {
                int val = read_memory(id, i, m);
                if (val != i)
                        success = 0;
                printf("%d ", val);

        }

        if (success)
                printf("\nSuccess!\n\n");
        else
                printf("\nFailure!\n\n");
        free_memory(&m);
}

int main(int argc, char *argv[])
{
        (void) argc;
        (void) argv;

        basic_test();
       
        exit(0);
}
