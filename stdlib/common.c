#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint64_t parse(char *s){
    // printf("parsing:%s ", s);
    char *end;
    long long v = strtoll(s, &end, 10);
    // printf("to:%llu\n", v);
    return v;
}

uint64_t count_char(char *str, char target){
    uint64_t count = 0;

    for (uint64_t i = 0; i < strlen(str); i++)
    {
        if(str[i] == target)
            count++;
    }
    return count;
}