#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../../stdlib/file.h"
int wrap(int value, int max);
void wrapCount(int *value, int max, int *count);

int main(){
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day01") != 0){
        perror("chdir");
        return 1;
    }
    char *data = fileDump("main_input1.txt");
    //printf("Data: %s\n", data);

    char *tok = strtok(data, "\n");
    int dial = 50;
    int points = 0;
    int row = 1;
    while (tok != NULL){
        //printf("-> %s", tok);
        char dir = tok[0];
        char *nums = tok+1;
        int num = dir == 'L' ? atoi(nums) * -1 :atoi(nums);
        //printf(" %c", dir);
        //printf(" %s\n", nums);
        //printf(" %d\n", num);
        tok = strtok(NULL, "\n");
        int count = 0;

        // printf("%d + %d = %d mod %d\n", dial, num, dial + num, wrap(dial + num, 100));
        int pDial = dial;
        dial += num;
        wrapCount(&dial , 100, &count);
        // printf("r:%d %d v: %d c: %d\n", row++ ,dial, num, count);
        printf("row:%d dial:%d move:%d passes:%d dialresult:%d\n",row++, pDial, num, count, dial);
        points += count;
        count = 0;
    }
    printf("Pwd is: %d\n", points);

    return 0;
}

int wrap(int value, int max){
    value %= max; 
    if(value < 0) value += max;
    return value;
}

void wrapCount(int *value, int max, int *count){
    if (*value >= max){
        *value -= max;
        (*count)++;
        wrapCount(value, max, count);
        return;
    }
    if (*value < 0){
        *value += max;
        (*count)++;
        wrapCount(value, max, count);
        return;
    }
    if(value == 0){
        (*count)++;
        return;
    }
}