#ifndef TESTING_H
#define TESTING_H

#define ROWS 100
#define COLS 3

#define TRAIN_SIZE 80
#define TEST_SIZE 20
#define FEATURES 2

void test_data(float data[ROWS][COLS], float test_X[TEST_SIZE][FEATURES], float test_y[TEST_SIZE]);
#endif
