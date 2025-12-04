#include <stdio.h>
#include <unistd.h>
#include "../../stdlib/file.h"
#include <stdbool.h>
#include <string.h>

bool example = true;
int main(){
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day04") != 0){
        perror("chdir");
        return 1;
    }
    char *data = example ? fileDump("example_input1.txt") : fileDump("main_input1.txt");
    char *token = strtok(data, "\n");
    
    while (token){
        printf("%s\n", token);
        token = strtok(NULL, "\n");
    }
    printf("%s\n", token);
    return 0;
}