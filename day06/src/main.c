#include <stdio.h>
#include <unistd.h>
#include "../../stdlib/file.h"
#include <stdbool.h>
#include <string.h>
#include "../../stdlib/common.h"
#include "../../stdlib/RMLinkedList.h"

typedef struct Problem{
    uint64_t nums[10];
    char operator;
    uint64_t result;
}Problem;

void calcProblem(Problem *problem);
bool example = false;
int main(){
    //problems = RMLinkedList_create();
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day06") != 0){
        perror("chdir");
        return 1;
    }
    char *data = example ? fileDump("example_input1.txt") : fileDump("main_input1.txt");
    uint64_t rows = count_char(data, '\n')+1;
    uint64_t elements = count_char(data, ' ') +1;
    printf("Row count:%llu\n", rows);
    char *save1;
    
    
    

    int i = 0;
    int row_num = 0;
    char *row = strtok_r(data, "\n", &save1);
    Problem problems[elements];
    memset(problems, 0, sizeof(problems));
    while(row){
        // printf("Row %d\n",row_num);
        char *save2;
        char *rowcpy = strdup(row);
        char *num_str = strtok_r(rowcpy, " ", &save2);
        if(row_num == rows-1){
            uint64_t c = 0;
            while(num_str){
                // printf("%s %d,", num_str, strlen(num_str));
                problems[c].operator = *num_str;
                c++;
                num_str = strtok_r(NULL, " ", &save2);
            }
        }
        else{
            uint64_t c = 0;
            while(num_str){
                // printf("%s,", num_str);
                problems[c].nums[row_num] = parse(num_str);
                c++;
                num_str = strtok_r(NULL, " ", &save2);
            }
        }
        // printf("\n");
        row_num++;
        row = strtok_r(NULL, "\n", &save1);
    }
    // printf("Data: %s\n", data);
    Problem *prop;
    uint64_t sum = 0;
    for(int j=0; j<elements; j++){
        prop = &problems[j];
        calcProblem(prop);
        sum += prop->result;
        // printf("Col:%d = %llu\n", j, prop->result);
        printf("%llu, %llu, %llu, %llu [%c] %llu\n", prop->nums[0],prop->nums[1],prop->nums[2],prop->nums[3],prop->operator, prop->result);
    }
     printf("Result:%llu\n", sum);
    return 0;
}


void calcProblem(Problem *problem){
    
    if (problem->operator == '*'){
        problem->result = 1;
        for (int32_t i = 0; i < 4; i++){
            problem->result *= problem->nums[i];
        }
    }
    else if(problem->operator == '+'){
        problem->result = 0;
        for (int32_t i = 0; i < 4; i++){
             problem->result += problem->nums[i];
        }
    }
}