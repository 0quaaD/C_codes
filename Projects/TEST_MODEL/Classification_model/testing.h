#ifndef TESTING_H
#define TESTING_H

#define ROWS 100
#define COLS 3

#define TRAIN_SIZE 80
#define TEST_SIZE 20
#define FEATURES 2
#define CAT_FEATURES 2 // there is 2 category 0 and 1
#define FINAL_FEATURES 1+CAT_FEATURES // this will determine the col size of encoded test_X

void test_data(float data[ROWS][COLS], float test_X[TEST_SIZE][FEATURES], float test_y[TEST_SIZE]);
void test_y_encoded(float test_y[TEST_SIZE], float test_y_encode[TEST_SIZE][FEATURES]);
void test_X_scaled(float test_X[TEST_SIZE][FEATURES], float test_X_sc[TEST_SIZE]);
#endif
