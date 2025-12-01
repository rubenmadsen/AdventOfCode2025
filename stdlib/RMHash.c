#include "RMHash.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define RM_HASH_OUTPUT
unsigned long hash_djb2(unsigned char *str) {
    unsigned char *hasher = (unsigned char*)strdup((char *)str);
    unsigned long hash = 5381;
    unsigned long c;
    while ((c = *hasher++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    #ifdef RM_HASH_OUTPUT
        printf("Hashed %s to %lu using %s", str, hash, "djb2\n");
    #endif
    free(hasher);
    return hash;
}
unsigned int rmhash(const char *key, size_t modulus){
    unsigned int value = 0;
    unsigned int key_len = strlen(key);
    for(unsigned int i=0; i<key_len; ++i){
        value = value * 37 + key[i];
    }
    value = value % modulus;
    #ifdef RM_HASH_OUTPUT
        //printf("Hashed %s to %d with modulus %zu\n",key,value,modulus);
    #endif
    return value;
}
uint32_t MurmurHash3_x86_32 ( const void * key, int len, uint32_t seed )
{
    const uint8_t * data = (const uint8_t*)key;
    const int nblocks = len / 4;
    uint32_t h1 = seed;
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

    for(int i = -nblocks; i; i++)
    {
        uint32_t k1 = blocks[i];
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> (32 - 13));
        h1 = h1*5+0xe6546b64;
    }

    const uint8_t * tail = (const uint8_t*)(data + nblocks*4);
    uint32_t k1 = 0;

    switch(len & 3)
    {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
            k1 *= c1; k1 = (k1 << 15) | (k1 >> (32 - 15)); k1 *= c2; h1 ^= k1;
    };

    h1 ^= len;
    h1 = h1 ^ (h1 >> 16);
    h1 *= 0x85ebca6b;
    h1 = h1 ^ (h1 >> 13);
    h1 *= 0xc2b2ae35;
    h1 = h1 ^ (h1 >> 16);

    return h1;
}
