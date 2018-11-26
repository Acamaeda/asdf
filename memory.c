/* memory.c
 * Homework 6 - UM Out
 * By Rhys Gilkenson and Harley White
 *
 * This is the implementation file for the Memory module.

 */

#include <stdlib.h>
#include "memory.h"
#include <seq.h>
#include <assert.h>
#include <stdio.h>
#include "uarray.h"
struct Memory{
        UArray_T segs;
        Seq_T free_ids;
        word next_id;
};

typedef struct Segment{
        word size;
        word *array;
} *Segment;

Memory new_memory()
{
        Memory m = malloc(sizeof(struct Memory));
        assert(m != NULL);

        m->segs = UArray_new(8, sizeof(struct Segment));
        m->free_ids = Seq_new(8);
        m->next_id = 0;
        return m;
}

word valid_addr(word seg, word addr, Memory mem)
{
        //fprintf(stderr, "%u %u \n", seg, addr);

        if (seg >= mem->next_id)
                return 0;
        
        Segment s = (Segment)UArray_at(mem->segs, seg);
        if (addr >= s->size)
                return 0;
        return 1;
}

word new_seg(word size, Memory mem)
{
        assert(size != 0);
        Segment s;
        word id;
        if (Seq_length(mem->free_ids) != 0) {
                word *idp = (word *)Seq_remlo(mem->free_ids);
                id = *idp;
                free(idp);
        }
        else {
                id = mem->next_id;
                mem->next_id++;
        }
        
        if (id >= (unsigned)UArray_length(mem->segs)){
                UArray_resize(mem->segs, (id * 2));
        }
        s = (Segment) UArray_at(mem->segs, id);
        s->size = size;
        s->array = calloc(size, sizeof(word));
        assert(s->array != NULL);
        
        return id;
}

void free_seg(word seg, Memory mem)
{
        assert(valid_addr(seg, 0, mem));
        Segment s = (Segment) UArray_at(mem->segs, seg);
        free(s->array);
        s->size = 0;
        word *segp = malloc(sizeof(word));
        *segp = seg;
        Seq_addhi(mem->free_ids, segp);
}


word read_memory(word seg, word addr, Memory mem)
{
        assert(valid_addr(seg, addr, mem));
        Segment s = (Segment) UArray_at(mem->segs, seg);
        return (s->array)[addr];
}
void write_memory(word seg, word addr, word value, Memory mem)
{
        assert(valid_addr(seg, addr, mem));
        Segment s = (Segment) UArray_at(mem->segs, seg);
        (s->array)[addr] = value;
}

void copy_seg(word src, word dest, Memory mem)
{
        assert(valid_addr(src, 0, mem));
        /* If dest is not already used it breaks our valid tests */
        assert(valid_addr(dest, 0, mem));

        Segment s1 = (Segment) UArray_at(mem->segs, src);
        Segment s2 = (Segment) UArray_at(mem->segs, dest);
        free(s2->array);

        s2->size = s1->size;
        s2->array = malloc(sizeof(word) * s1->size);
        for (unsigned i = 0; i < s1->size; i++) {
                (s2->array)[i] = (s1->array)[i];
        }
}


void free_memory(Memory *memm)
{
        Memory mem = *memm;
        UArray_T segs = mem->segs;
        for (int i = 0; i < UArray_length(segs); i ++){
                Segment seg = (Segment) UArray_at(segs, i);
                if(valid_addr(i, 0, mem) == 1)
                        free(seg->array);
        }
        for (int i = 0; i < Seq_length(mem->free_ids); i++)
                free((word*) Seq_get(mem->free_ids, i));
        UArray_free(&segs);
        Seq_free(&mem->free_ids);
        free(mem);     
}
