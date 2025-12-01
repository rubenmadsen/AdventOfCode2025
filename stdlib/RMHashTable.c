//
// Created by Ruben on 2023-01-30.
//


#include "RMHash.h"
#include "RMHashTable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RMIterator.h"
#include <RMStructs.h>


//// Private
void expandRMHashTable(RMHashTable *ht, size_t size);
RMHashTableEntry *createPair(char *key, void *value);


//// Public
RMHashTable *RMHashTable_create(){
    size_t size = 100;
    RMHashTable *ht = malloc(sizeof(RMHashTable));
    ht->mode = RM_STRING_MODE;
    ht->keySet = RMLinkedList_create();
    ht->size = size;
    ht->count = 0;
    ht->entries = malloc(sizeof(RMLinkedList *) * size);
    for(int i=0; i<size; i++){
        ht->entries[i] = NULL;
    }
    ht->putOut = false;
    ht->wlock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(ht->wlock,NULL);
    #ifdef RMHASHTABLE_PRINT
        printf("[Created RMHashTable with %zu preallocated entries. size:%zu bytes.]\n",size,sizeof(RMHashTableEntry) * size);
    #endif
    return ht;
}

void RMHashTable_destroy(RMHashTable *ht){
    RMLinkedList_destroy(ht->keySet);
    for(int i=0; i<ht->size; i++){
        if(ht->entries[i] != NULL)
            RMLinkedList_destroy(ht->entries[i]);
    }
    for(int i=0; i<ht->count; i++){
    }
    pthread_mutex_destroy(ht->wlock);
    free(ht->entries);
    free(ht);
}

RMHashTableEntry *createPair(char *key, void *value){
    RMHashTableEntry  *newEntry = malloc(sizeof(RMHashTableEntry));
    newEntry->key = key;
    newEntry->value = value;
    return newEntry;
}

void RMHashTable_put(RMHashTable *ht, char *key, void *value){
    char *dup_key = strdup(key);
    unsigned int hashed = rmhash(dup_key, ht->size);
    if(ht->putOut)
        printf("[%d]\n", hashed);
    RMLinkedList *list = ht->entries[hashed];
    pthread_mutex_lock(ht->wlock);
    // If slot is empty
    if(list == NULL){
        list = RMLinkedList_create();
        ht->entries[hashed] = list;
    }
    // list = RMLinkedList of hash table entries
    RMHashTableEntry *newEntry = createPair(dup_key,value);

    RMLinkedList_push(list,newEntry);
    RMLinkedList_push(ht->keySet, (void *)dup_key);
    ht->count++;
    pthread_mutex_unlock(ht->wlock);
}
void *RMHashTable_remove(RMHashTable *ht, char *key){
    unsigned int hashed = rmhash(key, ht->size);
 //   unsigned long hashed = hash_djb2(key) % ht->size;
    RMLinkedList *list = ht->entries[hashed];

    if(list == NULL){
        return NULL;
    }

    pthread_mutex_lock(ht->wlock);

    RMIterator *it = RMLinkedList_iterator(list);
    while(it->hasNext){
        RMHashTableEntry *entry = it->item;
        if (strcmp(entry->key, key) == 0){
            RMHashTableEntry *removed = RMLinkedList_popItem(list, entry);
            void *item = removed->value;
            free((void *)entry->key);
            free(it);
            free(removed);
            if(list->count == 0){
                RMLinkedList_destroy(ht->entries[hashed]);
                ht->entries[hashed] = NULL;
            }
            pthread_mutex_unlock(ht->wlock);
            return item;
        }
        it->next(it);
    }
    free(it);
    pthread_mutex_unlock(ht->wlock);
    return NULL;
}
RMHashTableEntry *RMHashTable_get_entry(RMHashTable *ht, char *key){
    unsigned int hashed = rmhash(key, ht->size);
    RMLinkedList *list = ht->entries[hashed];

    if(list == NULL){
        return NULL;
    }

    // Find value for key
    RMIterator *it = RMLinkedList_iterator(list);
    while (it->hasNext){
        RMHashTableEntry *entry = it->item;
        // Found match
        if(strcmp(entry->key,key) == 0){
            free(it);
            return entry;
        }
        it->next(it);
    }
    free(it);
    // Did not find match
    return NULL;
}
void *RMHashTable_get(RMHashTable *ht, char *key){
    RMHashTableEntry *entry = RMHashTable_get_entry(ht, key);
    if (entry == NULL)
        return NULL;
    else
        return entry->value;
}
char **RMHashTable_getKeys(RMHashTable *table){
//    int c = 0;
//    char **keys = malloc(sizeof(char *) * (table->size + 1));
//    for(size_t i=0; i<table->size; i++){
//        if(table->entries[i] != NULL){
//            keys[c] = table->entries[i]->key;
//            c++;
//        }
//    }
//    keys[c] = NULL;
//    return keys;
    return NULL;
}

bool RMHashTable_exist(RMHashTable *table, char *key){
    if(RMHashTable_get(table, key) == NULL)
        return false;
    return true;
}

//// RMIterator interface
void RMHashTable_next(RMIterator *it){
    it->hasNext = false;
//    free(it->item);
    RMIterator *lit = it->sub_iterator;
    lit->next(lit);
    if(lit->hasNext){
        it->hasNext = true;
        it->index++;
//        RMHashTableEntry *entry = malloc(sizeof(RMHashTableEntry));
//        entry->key = lit->item;
//        entry->value = RMHashTable_get(it->collection, (char *)entry->key);
//        it->item = entry;
        RMHashTableEntry *entry = RMHashTable_get_entry(it->collection, lit->item);
        it->cur = entry;
        it->item = entry->value;
    }
    else{
        free(lit);
    }
}
RMIterator *RMHashTable_iterator(RMHashTable *table){
    RMIterator *it = RMIterator_create();
    it->index = 0;
    it->collection = table;
    it->next = RMHashTable_next;
    table->iterator = it;
//    it->cur = RMHashTable_get_entry(table, it->item);

    // LinkedList
    RMIterator *lit = RMLinkedList_iterator(table->keySet);
    it->sub_iterator = lit;
    if(lit->hasNext){
        it->hasNext = true;
//        RMHashTableEntry *entry = malloc(sizeof(RMHashTableEntry));
//        entry->key = lit->item;
//        entry->value = RMHashTable_get(table, (char *)entry->key);
//        it->item = entry;

        RMHashTableEntry  *entry = RMHashTable_get_entry(table, lit->item);
        it->item = entry->value;
        it->cur = entry;
    }

    return  it;
}

//// Help
void RMHashTable_print(RMHashTable *ht){
    ForEach(RMHashTable_iterator(ht),{
        RMHashTableEntry *entry = it->cur;
        char print[64 + 1];
        bzero(print,64 +1);

    printf("%s", print);
        //printf("%s : %s -> %d",(char *)item, (char *)entry->value, type);
    });

//    RMIterator *it = RMHashTable_iterator(ht);
//    while (it->hasNext){
//        RMHashTableEntry *entry = it->item;
//        printf("%s : %s  ->%d\n",(char *)entry->key, (char *)entry->value), (int)entry->type;
//        it->next(it);
//    }
//    free(it);
}
