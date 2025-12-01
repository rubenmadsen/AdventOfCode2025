//
// Created by ruben on 8/30/23.
//

#include "RMQue.h"
#include "RMLinkedList.h"
#include "RMIterator.h"
#include <stdlib.h>

RMQue *RMQue_create(){
    RMQue *que = malloc(sizeof(RMQue));
    que->list = RMLinkedList_create();
    return que;
}
void RMQue_destroy(RMQue *que){
    RMLinkedList_destroy(que->list);
    free(que);
}

void RMQue_put(RMQue *que,void *item){
    RMLinkedList_push(que->list,item);
}

void *RMQue_take(RMQue *que){
    return RMLinkedList_popIndex(que->list,0);
}

//// Iterator
RMIterator *RMQue_next(RMIterator *it){

    return it;
}
RMIterator *RMQue_iterator(RMQue *que){
    RMIterator *it = RMIterator_create();

    return it;
}

//// Helpers
void RMWue_print(RMQue *que){

}