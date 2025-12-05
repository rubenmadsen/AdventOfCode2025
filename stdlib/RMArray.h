#ifndef RMARRAY_H
#define RMARRAY_H


typedef struct RMArray RMArray;

RMArray *rmarray_create(int initialSize);
void rmarray_destroy(RMArray *array);

void rmarray_add(RMArray *array, void *item);
void *rmarray_get(RMArray *array, int index);
void rmarray_remove(RMArray *array, int index);

#endif