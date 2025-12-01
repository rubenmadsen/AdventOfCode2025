//
// Created by ruben on 8/30/23.
//

#ifndef BLACKDUCK_RMQUE_H
#define BLACKDUCK_RMQUE_H
#include "RMLinkedList.h"
#include "RMIterator.h"

typedef struct RMQue RMQue;

struct RMQue{
    RMLinkedList *list;
};

/// Public
RMQue *RMQue_create();
void RMQue_destroy(RMQue *que);

void RMQue_put(RMQue *que,void *item);
void *RMQue_take(RMQue *que);

//// Iterator
RMIterator *RMQue_iterator(RMQue *que);

//// Helpers
void RMQue_print(RMQue *que);
#endif //BDFW_RMQUE_H
