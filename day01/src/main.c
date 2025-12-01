#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../../stdlib/file.h"
int wrap(int value, int max);
int wrapCount(int dial, int move, int *passes);

int main(){
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day01") != 0){
        perror("chdir");
        return 1;
    }
    char *data = fileDump("main_input1.txt");
    //printf("Data: %s\n", data);
    FILE *out = fopen("output.txt", "w");

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
        int pDial = dial;
        dial = wrapCount(dial, num, &count);
        
        fprintf(out, "row:%d dial:%d move:%d passes:%d dial after:%d\n",row++, pDial, num, count, dial);
        printf("row:%d dial:%d move:%d passes:%d dial after:%d\n",row++, pDial, num, count, dial);
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
int wrapCount(int dial, int move, int *passes){
    *passes = 0;

    int direction = (move >= 0 ? 1 : -1);
    int steps = abs(move);

    for(int i = 0; i < steps; i++){
        dial += direction;
        if (dial == 100) dial = 0;
        if (dial == -1) dial = 99;

        if (dial == 0)
            (*passes)++;
    }

    return dial;
}