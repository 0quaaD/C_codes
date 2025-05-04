#include "split_data.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void checkNull(float data[ROWS][COLS] )
{
   for(int i=0;i<ROWS;++i){
        for(int j=0;j<COLS;j++){
            if(isnan(data[i][j])){
                printf("\n\nData has NULL values!\n");
                return;
            }

        }
    }
    printf("Data is clean.\n");
}

void data_split(float data[ROWS][COLS])
{

    checkNull(data);
    float X[ROWS][NUM_FEATURES], y[ROWS];

    printf("\nENTIRE DATA\n");
    for(int i=0;i<ROWS;++i){
        for(int j=0;j<COLS;j++){
            if(j != COLS-1) printf("%.1f | ", data[i][j]);
            else printf("%.1f",data[i][j]);
        }
        printf("\n");
    }

    data_split_X(data);
    data_split_y(data);

    printf("\nX:\n");
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS-1;j++){
            if(j != COLS-2) printf("| %.1f | ",X[i][j]);
            else printf("%.1f |",X[i][j]);
        }
        printf("\n");
    }
    printf("\ny:\n");

    for(int i=0;i<ROWS;i++){
        printf("%.1f ",y[i]);
    }
}

float** data_split_X(float data[ROWS][COLS]){
    float** X = (float**)malloc(ROWS * sizeof(float*));
    for(int i=0;i<ROWS;i++){
        X[i] = (float*)malloc((COLS-1)*sizeof(float));
        for(int j=0;j<COLS-1;++j){
            X[i][j] = data[i][j];
        }

    }
    return X;
}

float* data_split_y(float data[ROWS][COLS])
{
    float* y = (float*)malloc(ROWS * sizeof(float));

    for(int i=0;i<ROWS;++i){
        y[i] =  data[i][2];
    }
    return y;
}


