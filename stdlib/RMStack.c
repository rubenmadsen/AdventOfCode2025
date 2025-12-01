//
// Created by ruben on 8/14/23.
//

#include "RMStack.h"
#include <stdlib.h>
#include <stdio.h>
#include "RMLinkedList.h"
#include "RMIterator.h"

RMStack *RMStack_create(){
    RMStack *stack = malloc(sizeof(RMStack));
    stack->list = RMLinkedList_create();
    return stack;
}
void RMStack_destroy(RMStack *stack){
    RMLinkedList_destroy(stack->list);
    free(stack);
}

void RMStack_put(RMStack *stack,void *item){
    RMLinkedList_push(stack->list,item);
}

void *RMStack_take(RMStack *stack){
    return RMLinkedList_pop(stack->list);
}

//// Iterator
RMIterator *RMStack_next(RMIterator *it){

    return it;
}
RMIterator *RMStack_iterator(RMStack *stack){
    RMIterator *it = RMIterator_create();

    return it;
}

//// Helpers
void RMStack_print(RMStack *stack){
    RMLinkedList_print(stack->list);
}