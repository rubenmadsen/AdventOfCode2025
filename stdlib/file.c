
#include "file.h"
#include <unistd.h>

char *fileDump(const char* filename){
    FILE *file = fopen(filename, "r");
    char cwd[256];
        if(getcwd(cwd, sizeof(cwd)) != NULL){
            printf("file: %s/%s\n", cwd, filename);
        } else {
            perror("getcwd");
        }
    if (file == NULL){
        perror("Could not find file.");
        return "";
    }
    size_t c = 0;
    fseek(file, 0, SEEK_END);
    c = ftell(file);
    rewind(file);
    char *data = (char *)calloc(c + 1 , sizeof(char));
    fread(data, sizeof(char), c, file);
    fclose(file);
    return data;
}