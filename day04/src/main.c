#include <stdio.h>
#include <unistd.h>
#include "../../stdlib/file.h"
#include <stdbool.h>
#include <string.h>

bool example = false;
typedef struct Cell { 
    int x;
    int y;
    char c;
    int ats;
} Cell;

void count_data_dimensions(char *data, int *rows, int * cols);
void get_ats(int rows, int cols, Cell cells[rows][cols], Cell *cell);
void print_grid(int rows, int cols, Cell cells[rows][cols]);
void apply_ats(int rows, int cols, Cell cells[rows][cols]);
void clear_ats(int rows, int cols, Cell cells[rows][cols]);
int count_ats(int rows, int cols, Cell cells[rows][cols]);
int main(){
    if(chdir("/Users/rubenmadsen/Advent of code/2025/day04") != 0){
        perror("chdir");
        return 1;
    }
    char *data = example ? fileDump("example_input1.txt") : fileDump("main_input1.txt");
    int rows = 0;
    int cols = 0;
    count_data_dimensions(data, &rows, &cols);
    Cell cells[rows][cols];
    printf("Rows:%d Cols:%d\n", rows, cols);
    char *token = strtok(data, "\n");
    
    int y = 0;
while (token && y < rows) {
    int line_len = strlen(token);

    for (int x = 0; x < cols; x++) {
        cells[y][x].x = x;
        cells[y][x].y = y;

        if (x < line_len)
            cells[y][x].c = token[x];
        else
            cells[y][x].c = '.';  

        cells[y][x].ats = 0;
    }

    y++;
    token = strtok(NULL, "\n");
}
    int count = 0;
    int accessible = 0;
    int count_before = count_ats( rows, cols, cells);
    do{    
        accessible = 0;
        for (size_t y = 0; y < rows; y++){
            for (size_t x = 0; x < cols; x++){
                Cell *cell = &cells[y][x];
                get_ats(rows, cols, cells, cell);
                if (cell->ats < 4 && cell->c == '@')
                {
                    accessible++;
                }
                
            }
            count += accessible;
        }
        printf("%d\n", accessible);
        apply_ats(rows, cols, cells);
        clear_ats(rows, cols, cells);
        print_grid(rows, cols, cells);
    } while (accessible != 0);
    int count_after = count_ats( rows, cols, cells);

    printf("%d\n", count_before-count_after);
    print_grid(rows, cols, cells);
    return 0;
}
int count_ats(int rows, int cols, Cell cells[rows][cols]){
    int count = 0;
    for (size_t y = 0; y < rows; y++){
        for (size_t x = 0; x < cols; x++){
            Cell *cell = &cells[y][x];
            if(cell->c == '@'){
                count++;
            }
        }
    }
    return count;
}
void apply_ats(int rows, int cols, Cell cells[rows][cols]){
    for (size_t y = 0; y < rows; y++){
        for (size_t x = 0; x < cols; x++){
            Cell *cell = &cells[y][x];
            if(cell->ats < 4 && cell->c == '@'){
                cell->c = '.';
            }
        }
    }
}

void clear_ats(int rows, int cols, Cell cells[rows][cols]){
    for (size_t y = 0; y < rows; y++){
        for (size_t x = 0; x < cols; x++){
            Cell *cell = &cells[y][x];
            cell->ats = 0;
        }
    }
}

void get_ats(int rows, int cols, Cell cells[rows][cols], Cell *cell){
    int x = cell->x;
    int y = cell->y;

    cell->ats = 0;

    // All 8 directions
    int dirs[8][2] = {
        {-1, -1}, { 0, -1}, { 1, -1},
        {-1,  0},           { 1,  0},
        {-1,  1}, { 0,  1}, { 1,  1}
    };

    for (int i = 0; i < 8; i++){
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];

        // bounds check
        if (nx < 0 || ny < 0 || nx >= cols || ny >= rows)
            continue;

        if (cells[ny][nx].c == '@')
            cell->ats++;
    }

}

void print_grid(int rows, int cols, Cell cells[rows][cols]) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            putchar(cells[y][x].c);
            // if (cells[y][x].ats < 4)
            //     putchar('x');
            // else
            //     putchar(cells[y][x].c);

        }
        putchar('\n');
    }
}


void count_data_dimensions(char *data, int *rows, int * cols){
    bool first = true;
    for (size_t i = 0; i < strlen(data); i++){
        if(data[i] == '\n'){
            if(first){
                *cols = i;
                first = false;
            }
            (*rows)++;
        }
    }
    (*rows)++;
}