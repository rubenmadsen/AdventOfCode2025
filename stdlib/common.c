#include "common.h"


uint64_t parse(char *s){
    // printf("parsing:%s ", s);
    char *end;
    long long v = strtoll(s, &end, 10);
    // printf("to:%llu\n", v);
    return v;
}