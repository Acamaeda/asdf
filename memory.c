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


inline Memory new_memory()
{
        Memory m = malloc(sizeof(struct Memory));
        assert(m != NULL);

        m->segs = UArray_new(8, sizeof(struct Segment));
        m->free_ids = Seq_new(8);
        m->next_id = 0;
        return m;
}

inline word valid_addr(word seg, word addr, Memory mem)
{
        if (seg >= mem->next_id)
                return 0;
        
        Segment s = (Segment)UArray_at(mem->segs, seg);
        if (addr >= s->size)
                return 0;
        return 1;
}

inline word new_seg(word size, Memory mem)
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

inline void free_seg(word seg, Memory mem)
{
        if (seg >= mem->next_id)
                assert(0);
        Segment s = (Segment)UArray_at(mem->segs, seg);
        if (0 >= s->size)
                assert(0);

        free(s->array);
        s->size = 0;
        word *segp = malloc(sizeof(word));
        *segp = seg;
        Seq_addhi(mem->free_ids, segp);
}


inline word read_memory(word seg, word addr, Memory mem)
{
        if (seg >= mem->next_id)
                assert(0);
        Segment s = (Segment)UArray_at(mem->segs, seg);
        if (addr >= s->size)
                assert(0);

        return (s->array)[addr];
}

inline void write_memory(word seg, word addr, word value, Memory mem)
{
        if (seg >= mem->next_id)
                assert(0);
        Segment s = (Segment)UArray_at(mem->segs, seg);
        if (addr >= s->size)
                assert(0);
        (s->array)[addr] = value;
}

inline void copy_seg(word src, word dest, Memory mem)
{
        if (src >= mem->next_id)
                assert(0);
        Segment s1 = (Segment)UArray_at(mem->segs, src);
        if (dest >= mem->next_id)
                assert(0);
        Segment s2 = (Segment)UArray_at(mem->segs, dest);

        free(s2->array);

        s2->size = s1->size;
        s2->array = malloc(sizeof(word) * s1->size);
        for (unsigned i = 0; i < s1->size; i++) {
                (s2->array)[i] = (s1->array)[i];
        }
}


inline void free_memory(Memory *memm)
{
        Memory mem = *memm;
        UArray_T segs = mem->segs;
        for (int i = 0; i < UArray_length(segs); i ++){
                if ((word)i < mem->next_id){
                        Segment s = (Segment)UArray_at(mem->segs, i);
                        if (0 < s->size)
                                free(s->array);
                }
        }
        for (int i = 0; i < Seq_length(mem->free_ids); i++)
                free((word*) Seq_get(mem->free_ids, i));
        UArray_free(&segs);
        Seq_free(&mem->free_ids);
        free(mem);     
}
