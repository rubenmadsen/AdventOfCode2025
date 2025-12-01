//
// Created by ruben on 1/30/23.
//

#ifndef BLACKDUCK_RMLINKEDLIST_H
#define BLACKDUCK_RMLINKEDLIST_H

#include <stdio.h>
#include <stdbool.h>
#include "RMIterator.h"
#include <pthread.h>

//// Typedefs
typedef struct RMLinkedListItem RMLinkedListItem;
typedef struct RMLinkedList RMLinkedList;
//// Structs
struct RMLinkedListItem{
    RMLinkedListItem *previous;
    void *item;
    RMLinkedListItem *next;
};
struct RMLinkedList{
    bool isEmpty;
    size_t count;
    RMLinkedListItem *head;
    RMLinkedListItem *tail;
    RMIterator *iterator;
    pthread_mutex_t *wlock;
};


//// Public
RMLinkedList *RMLinkedList_create(void);
void RMLinkedList_destroy(RMLinkedList *list);
//
void RMLinkedList_push(RMLinkedList *list, void *item);

unsigned int RMLinkedList_insertAt(RMLinkedList *list,void *item, unsigned int index);
void *RMLinkedList_getIndex(RMLinkedList  *list, unsigned int index);
void *RMLinkedList_pop(RMLinkedList *list);
void *RMLinkedList_popIndex(RMLinkedList  *list, unsigned int index);
void *RMLinkedList_popItem(RMLinkedList *list, void* item);
void RMLinkedList_clear(RMLinkedList *list);
bool RMLinkedList_exists(RMLinkedList *list, void *item);
void *RMLinkedList_head(RMLinkedList *list);
void *RMLinkedList_tail(RMLinkedList *list);
//// Iterator
RMIterator *RMLinkedList_iterator(RMLinkedList *list);

//// Help
void RMLinkedList_print(RMLinkedList *list);
#endif //REMOTE_HASHMAP_H
