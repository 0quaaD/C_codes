#include "testing.h"

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
