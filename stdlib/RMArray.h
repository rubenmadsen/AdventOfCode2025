//
// Created by ruben on 8/31/23.
//

#ifndef BLACKDUCK_RMARRAY_H
#define BLACKDUCK_RMARRAY_H
// Forward declaration
typedef struct RMIterator RMIterator;

// Typedefs
typedef struct RMArray RMArray;

// Structs

// Public
RMArray *RMArray_create(int capacity);
void RMArray_destroy(RMArray *array);
void *RMArray_get(RMArray *array, int index);
void RMArray_set_at(RMArray *array, void *element, int index);
int RMArray_count(RMArray *array);
void RMArray_remove(RMArray *arr, int index);


// Iterator
RMIterator *RMArray_iterator(RMArray *arr);

// Helpers
void RMArray_print(RMArray *arr);
#endif //BDFW_RMARRAY_H
