//
// Created by ruben on 8/29/23.
//

#ifndef BLACKDUCK_RMITERATOR_H
#define BLACKDUCK_RMITERATOR_H
#include <stdbool.h>

// Forward declaration
typedef struct RMIterator RMIterator;

RMIterator *RMIterator_create();
void RMIterator_destroy(RMIterator *it);
#endif //BDFW_RMITERATOR_H
