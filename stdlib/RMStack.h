//
// Created by ruben on 8/14/23.
//

#ifndef BLACKDUCK_RMSTACK_H
#define BLACKDUCK_RMSTACK_H
#include "RMLinkedList.h"
#include "RMIterator.h"

typedef struct RMStack RMStack;

struct RMStack{
   RMLinkedList *list;
};


//// Public
RMStack *RMStack_create();
void RMStack_destroy(RMStack *stack);

void RMStack_put(RMStack *stack,void *item);
void *RMStack_take(RMStack *stack);

//// Iterator
RMIterator *RMStack_iterator(RMStack *stack);

//// Helpers
void RMStack_print(RMStack *stack);
#endif //BDFW_RMSTACK_H
