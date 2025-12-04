#include <stdio.h>
#include <unistd.h>
#include "../../stdlib/file.h"
#include <stdbool.h>
#include <string.h>

uint64_t find_largest(char *str);
uint64_t part2_find_largest(char *str);
uint64_t parse(char *s);

bool example = false;
int main(){
    uint64_t sum = 0;
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day03") != 0){
        perror("chdir");
        return 1;
    }
    char *data = example ? fileDump("example_input1.txt") : fileDump("main_input1.txt");
    // printf("Data:\n%s\n", data);

    char *token = strtok(data, "\n");
    while (token){
        uint64_t nr = part2_find_largest(token);
        printf("%s - %llu\n", token, nr);
        sum += nr;
        token = strtok(NULL, "\n");
    }
    printf("Sum:%llu\n", sum);
    return 0;
}


uint64_t find_largest(char *str){

    uint64_t largest = 0;

    for (int i = 0; i < strlen(str)-1; i++){
        char nr[3] = {0,0,0};
        nr[0] = str[i];
        for (int j = i+1; j < strlen(str); j++){
            nr[1] = str[j];
            uint64_t num = parse(nr);
            if(largest<num)
                largest = num;
            //printf("Number: %llu\n", num);
        }
         printf("%s\n", nr);
    }
    return largest;
}

bool check_for_higher(char *str, char target){
    for (size_t i = 0; i < strlen(str); i++){
        if(str[i] > target)
            return true;
    }
    return false;
}

uint64_t part2_find_largest(char *str) {
    int len = strlen(str);
    int need = 12;

    char result[13];
    int r = 0;

    int pos = 0;
    while (need > 0) {
        int remaining = need;
        int maxStart = len - remaining;
        char bestDigit = '0';
        int bestIndex = pos;

        for (int i = pos; i <= maxStart; i++) {
            if (str[i] > bestDigit) {
                bestDigit = str[i];
                bestIndex = i;
            }
        }

        result[r++] = bestDigit;
        pos = bestIndex + 1;
        need--;
    }

    result[12] = '\0';
    return strtoull(result, NULL, 10);
}

uint64_t parse(char *s){
    char *end;
    long long v = strtoll(s, &end, 10);
    return v;
}