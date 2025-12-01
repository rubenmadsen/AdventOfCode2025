//
// Created by ruben on 8/31/23.
//

#include "RMArray.h"
#include <stdlib.h>
#include <stdio.h>
#include "RMIterator.h"
#include <RMCore.h>
#include <RMStructs.h>
/// Private
struct RMArray{
    int count;
    size_t capacity;
    void **array;
};
void resize_array(RMArray *arr, size_t capacity){
    arr->array = (void **) realloc(arr->array, capacity * sizeof(void *));
    size_t old_cap = capacity;
    arr->capacity = capacity;
    for (int i = old_cap; i < arr->capacity; ++i) {
        arr->array[i] = NULL;
    }
}
/// Public
RMArray *RMArray_create(int capacity){
    RMArray *arr = malloc(sizeof(RMArray));
    arr->count = 0;
    arr->array = malloc(capacity * sizeof(void *));
    resize_array(arr, capacity);
    return arr;
}

void *RMArray_get(RMArray *array, int index){
    return array->array[index];
}
void RMArray_remove(RMArray *arr, int index){
    arr->array[index] = NULL;
}
void RMArray_set_at(RMArray *array, void *element, int index){
//    if(index >= array->capacity) {
//        printf("Index out of bounds. \n");
//        return;
//    }
    if(array->count == array->capacity){
        resize_array(array, array->capacity*2);
    }
    if(array->array[index] == NULL)
        array->count++;
    array->array[index] = element;
}
int RMArray_count(RMArray *array){
    return array->count;
}

void RMArray_destroy(RMArray *array){
    free(array->array);
    free(array);
}


/// RMIterator
void RMArray_next(RMIterator it){

}
RMIterator *RMArray_iterator(RMArray *arr){
    RMIterator *it = RMIterator_create();
    it->collection = arr;

    return it;
}

// Helpers
void RMArray_print(RMArray *arr){
    printf("%d elements.\n", RMArray_count(arr));
    printf("Capacity %zu\n", arr->capacity);
    for (int i = 0; i < arr->capacity; ++i) {
        printf("\tIndex %d = %d\n", i, *(int*) RMArray_get(arr, i));
    }
}