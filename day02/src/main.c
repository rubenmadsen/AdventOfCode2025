#include <stdio.h>
#include <unistd.h>
#include "../../stdlib/file.h"
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

int countOccurences(char *str, const char *target);
bool part1_isValid(char *str);
bool part2_isValid(char *str);
uint64_t parse(char *s);

uint64_t total = 0;
int main(){
    // int occ = countOccurences("111111", "1"); // 6
    // printf("Occurences:%d\n", occ);
    // occ = countOccurences("121212", "12"); // 6
    // printf("Occurences:%d\n", occ);
    // occ = countOccurences("12341234", "1234"); // 6
    // printf("Occurences:%d\n", occ);
    // occ = countOccurences("123451234", "12345"); // 6
    // printf("Occurences:%d\n", occ);
    // return 99;
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day02") != 0){
        perror("chdir");
        return 1;
    }
    char *data = fileDump("main_input1.txt");
    printf("Data: %s\n", data);
    char *save;
    char *token = strtok_r(data, ",", &save);

    while (token){
        printf("token%s\n", token);
        
        char *firstPart = strtok(token, "-");
        u_int64_t first = parse(firstPart);
        char *secPart = strtok(NULL, "-");
        uint64_t sec = parse(secPart);
        token = strtok_r(NULL, ",", &save);
        printf("First:%d Second:%d\n", first, sec);
        
        for (uint64_t i = first; i <=sec; i++){
            char txt[32];
            sprintf(txt, "%" PRIu64, i);
            bool isNotValid = part2_isValid(txt);

            printf("Number: %" PRIu64 " isValid:%d\n", i, isNotValid);
            if(isNotValid)
                total += (u_int64_t)i;
            printf("Total:%" PRIu64 "\n", total);
            if(total < 0)
                break;
        }
        //break;
        
    }
    printf("Total:%" PRIu64 "\n", total);
    
    return 0;
}
int countOccurences(char *str, const char *target){
    int count = 0;
    int len = strlen(target);
    char *cur = str;

    while (strncmp(cur, target, len) == 0){
        count++;
        cur += len;
    }
    return count;
}

bool part2_isValid(char *str){
    int len = strlen(str);

    for (int p = 1; p <= len/2; p++){
        if (len % p != 0)
            continue;

        int reps = len / p;
        if (reps < 2)
            continue;

        bool ok = true;
        for (int r = 1; r < reps; r++){
            if (strncmp(str, str + r*p, p) != 0){
                ok = false;
                break;
            }
        }

        if (ok)
            return true;
    }

    return false;
}

bool part1_isValid(char *str){
    int len = strlen(str);

    if(len % 2 != 0)
        return false;   

    int half = len / 2;

    return strncmp(str, str + half, half) == 0;
}

uint64_t parse(char *s){
    char *end;
    long long v = strtoll(s, &end, 10);
    return v;
}