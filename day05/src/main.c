#include <stdio.h>
#include <unistd.h>
#include "../../stdlib/file.h"
#include <stdbool.h>
#include <string.h>
#include "RMLinkedList.h"
#include "RMIterator.h"

#define ForEach(iterator, lambda)        \
{                                        \
    RMIterator *it = iterator;           \
    while (it->hasNext) {                \
        void *item = it->item;           \
        lambda                           \
        it->next(it);                    \
    }                                    \
    free(it);                            \
}

typedef struct Range{
    uint64_t start;
    uint64_t end;
} Range;
bool inRange(Range *range, uint64_t target);
bool inList(uint64_t target);
uint64_t parse(char *s);
RMLinkedList *list;

bool example = false;
int main(){
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day05") != 0){
        perror("chdir");
        return 1;
    }
    list = RMLinkedList_create();
    char *data = example ? fileDump("example_input1.txt") : fileDump("main_input1.txt");
    char *first = data;
    char *second = strstr(data, "\n\n");
    *second = '\0';
    second += 2;

    // printf("First:%s\n",first);
    // printf("Second:%s\n", second);

    char *save;
    char *row = strtok_r(first, "\n", &save);

    while (row){
        char *first_num = strtok(row, "-");
        char *second_num = strtok(NULL, "-");

        uint64_t fnum = parse(first_num);
        uint64_t snum = parse(second_num);
        Range *range = calloc(1, sizeof(Range));
        range->start = fnum;
        range->end = snum;
        RMLinkedList_push(list, range);
        row = strtok_r(NULL, "\n", &save);
    }
    row = strtok_r(second, "\n", &save);
    uint64_t available = 0;
    while(row){
        uint64_t num = parse(row);
        if(inList(num)){
            available++;
        }
       row = strtok_r(NULL, "\n", &save);
    }
    printf("Available:%llu\n", available);
    return 0;
}




bool inRange(Range *range, uint64_t target){
    char *res = (target >= range->start && target <= range->end) ? "yes":"no";
    printf("Is %d in range %d - %d.  ->  %s\n", target, range->start, range->end, res);
    return (target >= range->start && target <= range->end);
}

bool inList(uint64_t target){
    RMLinkedListItem *cur = list->head;
    while(cur){
        Range *range = (Range *)cur->item;
        if(inRange(range, target))
            return true;
        cur = cur->next;
    }
    return false;
}
uint64_t parse(char *s){
    printf("parsing:%s ", s);
    char *end;
    long long v = strtoll(s, &end, 10);
    printf("to:%llu\n", v);
    return v;
}