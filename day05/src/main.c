#include <stdio.h>
#include <unistd.h>
#include "../../stdlib/file.h"
#include <stdbool.h>
#include <string.h>
#include "../../stdlib/RMLinkedList.h"
#include "RMIterator.h"


typedef struct Range{
    uint64_t start;
    uint64_t end;
} Range;
bool sort(void *A, void *B);
void removeDuplicates(RMLinkedList *list);
bool inRange(Range *range, uint64_t target);
bool inList(uint64_t target);
bool findIndex(uint64_t target);
uint64_t parse(char *s);
RMLinkedList *list;
RMLinkedList *indicies;
uint64_t fresh = 0;

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

    char *save1;
    char *row = strtok_r(first, "\n", &save1);

    while (row){
        char *first_num = strtok(row, "-");
        char *second_num = strtok(NULL, "-");

        uint64_t fnum = parse(first_num);
        uint64_t snum = parse(second_num);
        Range *range = calloc(1, sizeof(Range));
        range->start = fnum;
        range->end = snum;
        RMLinkedList_push(list, range);
        row = strtok_r(NULL, "\n", &save1);
    }
    char *save2;
    row = strtok_r(second, "\n", &save2);
    uint64_t available = 0;
    while(row){
        uint64_t num = parse(row);
        if(inList(num)){
            available++;
        }
       row = strtok_r(NULL, "\n", &save2);
    }
    printf("Available:%llu\n\n", available);
    //
    // Part 2
    //
    fresh = 0;
    
    RMLinkedList_sort(list, sort);
    RMLinkedListItem *cur = list->head;
   
    cur = list->head;
    while (cur->next){
        
        Range *current = cur->item;
        Range *next = cur->next->item;

        // If before 
        if(current->start < next->start && current->end < next->start){
            
        }
        // If within
        else if(inRange(next, current->start) && inRange(next, current->end)){
            RMLinkedList_popItem(list, cur);
        
        }
        else{
            current->end = next->start-1;
            if(current->end < current->start)
                current->end = current->start;
        }
        
        cur = cur->next;
         // uint64_t offset = ((Range *)list->head->item)->start;
    // while (cur->next){
    //     Range *range = cur->item;
    //     range->start -= offset;
    //     range->end -= offset;
    //     cur = cur->next;
    // }
    }
    removeDuplicates(list);
        
    // cur = indicies->head;
    // while (cur){
    //     printf("%llu, ", cur->item);
    //     cur = cur->next;
    // // 344771884978261
    // // 330297823873817
    cur = list->head;
    while (cur){
        Range *current = cur->item;
        fresh += current->end - current->start;
        printf("Range: %llu -> %llu = %llu\n", current->start, current->end, current->end - current->start);
        cur = cur->next;
    }
    cur = list->head;
    printf("\nFresh:%llu\n", fresh);

    return 0;
}

bool findIndex(uint64_t target){
    RMLinkedListItem *cur = indicies->head;
    while(cur){
        if (*(uint64_t *)cur->item == target){
            return true;
        }
        
        cur = cur->next;
    }
    return false;
}
void removeDuplicates(RMLinkedList *list) {
    RMLinkedListItem *cur = list->head;

    while (cur != NULL) {
        Range *a = cur->item;

        RMLinkedListItem *runner = cur->next;

        while (runner != NULL) {
            RMLinkedListItem *next = runner->next;
            Range *b = runner->item;

            if (a->start == b->start && a->end == b->end) {
                // b is a duplicate of a
                RMLinkedList_popItem(list, b);
            }

            runner = next;
        }

        cur = cur->next;
    }
}


bool inRange(Range *range, uint64_t target){
    //char *res = (target >= range->start && target <= range->end) ? "yes":"no";
    //printf("Is %d in range %d - %d.  ->  %s\n", target, range->start, range->end, res);
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
    // printf("parsing:%s ", s);
    char *end;
    long long v = strtoll(s, &end, 10);
    // printf("to:%llu\n", v);
    return v;
}

bool sort(void *A, void *B) {
    Range *a = (Range*)A;
    Range *b = (Range*)B;
    // printf("Sorting:%llu and %llu\n", a->start, b->start);
    return a->start <= b->start;
}
