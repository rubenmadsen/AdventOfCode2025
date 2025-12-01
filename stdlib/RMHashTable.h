//
// Created by Ruben on 2023-01-30.
//

#ifndef BLACKDUCK_RMHASHTABLE_H
#define BLACKDUCK_RMHASHTABLE_H
#include "RMHash.h"
#include <stddef.h>
#include <stdint.h>
#include "RMLinkedList.h"
#include "RMIterator.h"
#include <pthread.h>

//// Typedefs
typedef struct RMHashTable RMHashTable;
typedef struct RMHashTableEntry RMHashTableEntry;
typedef enum RMHashTableMode RMHashTableMode;

//// Enums
enum RMHashTableMode{
    RM_STRING_MODE,
    RM_OBJECT_MODE,
    RM_PRIMITIVE_MODE
};

//// Structs
struct RMHashTable{
    RMHashTableMode mode;
    RMLinkedList *keySet;
    size_t size;
    uint32_t count;
    RMLinkedList **entries;
    RMIterator *iterator;
    pthread_mutex_t *wlock;
    bool putOut;
};
struct RMHashTableEntry{
    char *key;
    void *value;
};
//// Private
void RMHashTable_expand(RMHashTable *ht, size_t size);

//// Public
RMHashTable *RMHashTable_create();
void RMHashTable_destroy(RMHashTable *ht);

//
void RMHashTable_put(RMHashTable *ht, char *key, void *value);
void *RMHashTable_remove(RMHashTable *ht, char *key);
void *RMHashTable_get(RMHashTable *ht, char *key);
RMHashTableEntry *RMHashTable_get_entry(RMHashTable *ht, char *key);
char **RMHashTable_getKeys(RMHashTable *table);
bool RMHashTable_exist(RMHashTable *table, char *key);

//// Iterator
RMIterator *RMHashTable_iterator(RMHashTable *table);

//// Help
void RMHashTable_print(RMHashTable *ht);


#endif //HASH_RMHASHTABLE_H
