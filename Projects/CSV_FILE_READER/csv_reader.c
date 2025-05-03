#include "csv_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_rows(const char* filename)
{
    FILE* fp = fopen(filename,"r");
    if(!fp) return -1;
    int count = 0;
    char line[LINE_LEN];
    while(fgets(line, sizeof(line), fp)) count++;
    fclose(fp);
    return count;
}

int count_cols(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if(!fp) return -1;
    int count = 0;
    char line[LINE_LEN];

    while(!fgets(line, sizeof(line),fp)) return -1;

    fclose(fp);
    char* token = strtok(line,",");
    while(token){
        count++;
        token = strtok(NULL, ",");
    }
    return count;
}

int load_file(const char* filename, float X[200][9] , float y[200] )
{
    FILE* fp = fopen(filename, "r");
    if(!fp){
        perror("File cannot be opened!\n");
        return -1;
    }

    int row = 0;
    char line[LINE_LEN];
    fgets(line,sizeof(line),fp);
    while(fgets(line,sizeof(line),fp) && row < ROWS){
        int col = 0;
        char* token = strtok(line,",");
        while(token && col < COLS-1){
            X[row][col] = atof(token);
            token = strtok(NULL,",");
            col++;
        }
        if(token) y[row] = atoi(token);
        row++;
    }
    fclose(fp);
    return row;
}


