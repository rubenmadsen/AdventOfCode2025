#include "RMLinkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <RMCore.h>
#include <RMStructs.h>

// Private
void rmll_insert(RMLinkedList *list, RMLinkedListItem *before, RMLinkedListItem *item) {
    list->count++;
    RMLinkedListItem *after = before->next;
    before->next = item;
    item->previous = before;
    if (after != NULL) {
        after->previous = item;
    }
    item->next = after;
    if (before == list->tail) {
        list->tail = item;
    }
}

// Public
RMLinkedList *RMLinkedList_create() {
    RMLinkedList *list = malloc(sizeof(RMLinkedList));
    if (list == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    list->isEmpty = true;
    list->wlock = malloc(sizeof(pthread_mutex_t));
    if (list->wlock == NULL) {
        free(list);
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_init(list->wlock, NULL);
    return list;
}

void RMLinkedList_destroy(RMLinkedList *list) {
    pthread_mutex_lock(list->wlock);
    pthread_mutex_destroy(list->wlock);
    free(list->wlock);
    RMLinkedListItem *cur = list->head;
    while (cur != NULL) {
        RMLinkedListItem *next = cur->next;
        free(cur);
        cur = next;
    }
    free(list);
}

void RMLinkedList_clear(RMLinkedList *list) {
    pthread_mutex_lock(list->wlock);
    RMLinkedListItem *cur = list->head;
    while (cur != NULL) {
        RMLinkedListItem *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    list->isEmpty = true;
    pthread_mutex_unlock(list->wlock);
}

void RMLinkedList_push(RMLinkedList *list, void *item) {
    pthread_mutex_lock(list->wlock);
    RMLinkedListItem *newItem = malloc(sizeof(RMLinkedListItem));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        pthread_mutex_unlock(list->wlock);
        exit(EXIT_FAILURE);
    }
    newItem->item = item;
    newItem->previous = list->tail;
    newItem->next = NULL;

    if (list->head == NULL) {
        list->head = newItem;
        list->tail = newItem;
    } else {
        list->tail->next = newItem;
        list->tail = newItem;
    }
    list->count++;
    list->isEmpty = false;
    pthread_mutex_unlock(list->wlock);
}

unsigned int RMLinkedList_insertAt(RMLinkedList *list, void *item, unsigned int index) {
    pthread_mutex_lock(list->wlock);
    if (index > list->count) {
        printf("[WARNING: Index out of bounds.]\n");
        pthread_mutex_unlock(list->wlock);
        return -1;
    }
    RMLinkedListItem *newItem = malloc(sizeof(RMLinkedListItem));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        pthread_mutex_unlock(list->wlock);
        exit(EXIT_FAILURE);
    }
    newItem->item = item;
    if (index == 0) {
        newItem->next = list->head;
        newItem->previous = NULL;
        if (list->head != NULL) {
            list->head->previous = newItem;
        }
        list->head = newItem;
        if (list->tail == NULL) {
            list->tail = newItem;
        }
    } else {
        RMLinkedListItem *cur = list->head;
        for (unsigned int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }
        rmll_insert(list, cur, newItem);
    }
    pthread_mutex_unlock(list->wlock);
    return index;
}
void *RMLinkedList_head(RMLinkedList *list){
    return list->head;
}
void *RMLinkedList_tail(RMLinkedList *list){
    return list->tail;
}
void *RMLinkedList_pop(RMLinkedList *list) {
    pthread_mutex_lock(list->wlock);
    if (list->tail == NULL) {
        pthread_mutex_unlock(list->wlock);
        return NULL;
    }

    RMLinkedListItem *tail = list->tail;
    void *item = tail->item;

    if (list->tail == list->head) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = tail->previous;
        list->tail->next = NULL;
    }

    free(tail);
    list->count--;
    list->isEmpty = (list->count == 0);
    pthread_mutex_unlock(list->wlock);
    return item;
}

void *RMLinkedList_getIndex(RMLinkedList *list, unsigned int index) {
    if (index >= list->count) {
        printf("[WARNING: Index out of bounds.]\n");
        return NULL;
    }
    RMLinkedListItem *cur = list->head;
    for (unsigned int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->item;
}

void *RMLinkedList_popIndex(RMLinkedList *list, unsigned int index) {
    pthread_mutex_lock(list->wlock);
    if (index >= list->count) {
        pthread_mutex_unlock(list->wlock);
        return NULL;
    }

    RMLinkedListItem *cur = list->head;
    for (unsigned int i = 0; i < index; i++) {
        cur = cur->next;
    }

    void *item = cur->item;
    if (cur->previous != NULL) {
        cur->previous->next = cur->next;
    } else {
        list->head = cur->next;
    }

    if (cur->next != NULL) {
        cur->next->previous = cur->previous;
    } else {
        list->tail = cur->previous;
    }

    free(cur);
    list->count--;
    list->isEmpty = (list->count == 0);
    pthread_mutex_unlock(list->wlock);
    return item;
}

void *RMLinkedList_popItem(RMLinkedList *list, void *item) {
    pthread_mutex_lock(list->wlock);
    RMLinkedListItem *cur = list->head;
    while (cur != NULL) {
        if (cur->item == item) {
            if (cur->previous != NULL) {
                cur->previous->next = cur->next;
            } else {
                list->head = cur->next;
            }

            if (cur->next != NULL) {
                cur->next->previous = cur->previous;
            } else {
                list->tail = cur->previous;
            }

            free(cur);
            list->count--;
            list->isEmpty = (list->count == 0);
            pthread_mutex_unlock(list->wlock);
            return item;
        }
        cur = cur->next;
    }
    pthread_mutex_unlock(list->wlock);
    return NULL;
}

bool RMLinkedList_exists(RMLinkedList *list, void *item) {
    RMLinkedListItem *cur = list->head;
    while (cur != NULL) {
        if (cur->item == item) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// RMIterator interface
void RMLinkedList_next(RMIterator *it) {
    RMLinkedListItem *listItem = it->cur;
    if (listItem->next != NULL) {
        it->hasNext = true;
        it->index++;
        it->cur = listItem->next;
        it->item = listItem->next->item;
    } else {
        it->hasNext = false;
    }
}

RMIterator *RMLinkedList_iterator(RMLinkedList *list) {
    RMIterator *it = RMIterator_create();
    it->index = 0;
    it->collection = list;
    it->next = RMLinkedList_next;
    list->iterator = it;

    if (list->head != NULL) {
        it->hasNext = true;
        it->item = list->head->item;
        it->cur = list->head;
    } else {
        it->hasNext = false;
        it->item = NULL;
        it->cur = NULL;
    }

    return it;
}

// Helpers
void RMLinkedList_print(RMLinkedList *list) {
    unsigned int c = 0;
    printf("\n%zu posts: (%zu + %zu) bytes\n", list->count, sizeof(RMLinkedList), (sizeof(RMLinkedListItem) * list->count));
    if (list->head != NULL) {
        RMLinkedListItem *cur = list->head;
        while (cur != NULL) {
            printf("\tItem at index %d -> %s\n", c, (char *)cur->item);
            c++;
            cur = cur->next;
        }
    }
}