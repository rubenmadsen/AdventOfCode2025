//
// Created by ruben on 8/29/23.
//

#include <RMCore.h>
#include <RMStructs.h>
#include <stdlib.h>


RMIterator *RMIterator_create(){
    RMIterator *it = malloc(sizeof(RMIterator));
    it->hasNext = false;
    it->collection = NULL;
    it->sub_iterator = NULL;
    it->item = NULL;
    it->cur = NULL;
    it->next = NULL;
    it->index = 0;
    return it;
}

void RMIterator_destroy(RMIterator *it){
    free(it);
}