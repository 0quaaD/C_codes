#include "testing.h"

void test_data(float data[ROWS][COLS], float test_X[TEST_SIZE][FEATURES], float test_y[TEST_SIZE]){
    for(int i=0;i<TEST_SIZE;i++){
        test_y[i] = data[i + TRAIN_SIZE][FEATURES];
        for(int j=0;j<FEATURES;j++){
            test_X[i][j] = data[i + TRAIN_SIZE][j];
        }
    }
}
