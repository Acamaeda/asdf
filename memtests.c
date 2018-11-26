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

void copy_test()
{
        printf("Performing copy test\n");
        Memory m = new_memory();
        int success = 1;
        int id = new_seg(10, m); /* Make two segments */
        id = new_seg(10, m); 

        for (int i = 0; i < 10; i++)
                write_memory(id, i, i, m);

        copy_seg(id, 0, m);
        for (int i = 0; i < 10; i++) {
                int val = read_memory(0, i, m);
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

void recycle_test()
{
        printf("Performing recycle test\n");
        Memory m = new_memory();
        int id = 0;
        for(int i = 0; i < 1000; i++) {
                for (int j = 0; j < 3; j++) {
                        id = new_seg(1024, m);
                }
                free_seg(0, m);
                free_seg(1, m);
                free_seg(2, m);
        }
        if (id == 2)
                printf("Success!\n\n");
        else
                printf("Failure!\n\n");
        free_memory(&m);
}

void delete_twice()
{
        printf("Performing delete twice\n");
        Memory m = new_memory();
        int seg = new_seg(5, m);
        free_seg(seg, m);
        free_seg(seg, m);
        free_memory(&m);
        printf("Success!\n\n");
}

void out_of_bounds()
{
        printf("Performing out of bounds\n");
        Memory m = new_memory();
        int seg = 5;
        int address = 10;
        printf("%d", (read_memory(seg, address, m)));
        free_memory(&m);
        printf("Success!\n\n");
}

void access_freed()
{
        printf("Performing access freed\n");
        unsigned input = 2;
        Memory m = new_memory();
        int seg = new_seg(5, m);
        write_memory(seg, 0, input, m);
        free_seg(seg, m);
        printf("%d", read_memory(seg, 0, m));
        if (read_memory(seg, 0, m) == input)
                printf("Failure!\n\n");
        else 
                printf("Success!\n\n");
        free_memory(&m);
}

void valid_test()
{
        printf("Performing valid test\n");
        int success = 1;
        Memory m = new_memory();
        int seg = new_seg(5, m);
        
        if (valid_addr(seg, 0, m) != 1)
                success = 0;
        free_seg(seg, m);
        if (valid_addr(seg, 0, m) != 0)
                success = 0;

        if (success)
                printf("Success!\n\n");
        else 
                printf("Failure!\n\n");
        free_memory(&m);
}


int main(int argc, char *argv[])
{
        (void) argc;
        (void) argv;

        //basic_test();
        //copy_test();
        //recycle_test();

        //delete_twice();
        //out_of_bounds();
        //access_freed();
        //valid_test();
        exit(0);
}
