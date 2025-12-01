//
// Created by ruben on 7/21/23.
//

#ifndef BLACKDUCK_RMHASH_H
#define BLACKDUCK_RMHASH_H
#include <stdio.h>
#include <stdint.h>

unsigned long hash_djb2(unsigned char *str);
unsigned int rmhash(const char *key, size_t modulus);
uint32_t MurmurHash3_x86_32 ( const void * key, int len, uint32_t seed);
#endif //BDFW_RMHASH_H
