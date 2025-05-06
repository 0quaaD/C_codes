#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

void test_data(float data[ROWS][COLS], float test_X[TEST_SIZE][FEATURES], float test_y[TEST_SIZE]){
    for(int i=0;i<TEST_SIZE;i++){
        test_y[i] = data[i + TRAIN_SIZE][FEATURES];
        for(int j=0;j<FEATURES;j++){
            test_X[i][j] = data[i + TRAIN_SIZE][j];
        }
    }
}

void test_y_encoded(float test_y[TEST_SIZE], float test_y_encode[TEST_SIZE][FEATURES]){
    for(int i=0;i<TEST_SIZE;i++){
        int cat = (int)test_y[i];
        for(int j=0;j<FEATURES;j++){
            test_y_encode[i][j] = (j == cat) ? 1.0f : 0.0f;
        }
    }
}

void test_X_scaled(float test_X[TEST_SIZE][FEATURES], float test_X_sc[TEST_SIZE]){
    float min = test_X[0][0], max = test_X[0][0];
    for(int i=0;i<TEST_SIZE;i++){
        if(min > test_X[i][0]) min = test_X[i][0];
        if(max < test_X[i][0]) max = test_X[i][0];
    }
    printf("test_X --> min : %.1f, max : %.1f\n",min,max);

    float range = max - min;
    if(range == 0){
        perror("Test X cannot scaled!");
        exit(1);
    }
    for(int i=0;i<TEST_SIZE;i++){
        test_X_sc[i] = (test_X[i][0] - min) / range;
        
        for(int j=0;j<FEATURES;j++){

        }
    }
}
