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



float** data_split_X(float data[ROWS][COLS]){
    float** X = (float**)malloc(ROWS * sizeof(float*));
    if(!X){
        fprintf(stderr, "DATASPLITX X array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<ROWS;i++){
        X[i] = (float*)malloc((COLS-1)*sizeof(float));
        if(!X[i]){
            fprintf(stderr, "DATASPLIT X[i] array allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        for(int j=0;j<COLS-1;++j){
            X[i][j] = data[i][j];
        }

    }
    return X;
}

float* data_split_y(float data[ROWS][COLS])
{
    float* y = (float*)malloc(ROWS * sizeof(float));
    if(!y){
        fprintf(stderr, "DATASPLITY Y array allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<ROWS;++i){
        y[i] =  data[i][2];
    }
    return y;
}

float** train_X_data(float data[ROWS][COLS]){
    float** train_X = (float**)malloc(TRAIN_SIZE * sizeof(float*));
    if(!train_X){
        fprintf(stderr, "TRAINXDATA train_X allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<TRAIN_SIZE;i++){
        train_X[i] = (float*)malloc(NUM_FEATURES * sizeof(float));
        if(!train_X[i]){
            fprintf(stderr, "TRAINXDATA X[i] allocation failed!\n");
            exit(EXIT_FAILURE);
        }

    }
    for(int i=0;i<TRAIN_SIZE;i++){
        for(int j=0;j<NUM_FEATURES;j++){
            train_X[i][j] = data[i][j];
        }
    }
    return train_X;
}

float* train_y_data(float data[ROWS][COLS]){
    float* train_y = (float*)malloc(TRAIN_SIZE * sizeof(float));
    if (!train_y) {
        fprintf(stderr, "Memory allocation failed for train_y\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<TRAIN_SIZE;i++){
        train_y[i] = data[i][NUM_FEATURES];
    }
    return train_y;
}

float** test_X_data(float data[ROWS][COLS]){
    float** test_X = (float**)malloc(TEST_SIZE * sizeof(float*));
    if (!test_X) {
        fprintf(stderr, "Memory allocation failed for test_X\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<TEST_SIZE;i++){
        test_X[i] = (float*)malloc(NUM_FEATURES * sizeof(float));
        if (!test_X) {
            fprintf(stderr, "Memory allocation failed for test_X[i]\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0;i<TEST_SIZE;i++){
        for(int j=0;j<NUM_FEATURES;j++){
            test_X[i][j] = data[i + TRAIN_SIZE][j];
        }
    }
    return test_X;
}

float* test_y_data(float data[ROWS][COLS]){
    float* test_y = (float*)malloc(TEST_SIZE * sizeof(float));
    if (!test_y) {
        fprintf(stderr, "Memory allocation failed for test_y\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<TEST_SIZE;i++){
        test_y[i] = data[i+TRAIN_SIZE][NUM_FEATURES];
    }
    return test_y;
}

void free_2d_arr(float** arr, int rows){
    for(int i=0;i<rows;i++) free(arr[i]);
    free(arr);
}

void free_model_mem(float* z, float* pred){
    free(z); free(pred);
}
