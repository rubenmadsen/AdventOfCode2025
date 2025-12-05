

#include "RMArray.h"
#include <stdlib.h>
#include <inttypes.h>

typedef struct WrapperItem{
    void *item;
} WrapperItem;

struct RMArray{
    WrapperItem *items;
    size_t capacity;
    u_int32_t cursor;
};


RMArray *rmarray_create(int initialSize){
    RMArray *array = (RMArray *)malloc(sizeof(RMArray));
    array->items = (WrapperItem *)malloc(sizeof(WrapperItem) * initialSize);
    array->capacity = initialSize;
    array->cursor = 0;
    for (size_t i = 0; i < array->capacity; i++){
        array->items[i].item = NULL;
    }
    
    return array;
}
void rmarray_destroy(RMArray *array){
    free(array->items);
    free(array);
}

void rmarray_add(RMArray *array, void *item){
    // WrapperItem *wrap = malloc(sizeof(WrapperItem));
    // wrap->item = item;
    array->items[array->cursor++].item = item;
}
void *rmarray_get(RMArray *array, int index){
    return array->items[index].item;
}
void rmarray_remove(RMArray *array, int index){
    
}

void expand(RMArray *array){
    void *new = realloc(array->items, array->capacity*2);
    array->items = new;
}

void contract(RMArray *array){

}