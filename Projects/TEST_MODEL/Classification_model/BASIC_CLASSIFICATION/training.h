#ifndef TRAINING_H
#define TRAINING_H

#define ROWS 100
#define COLS 3
#define FEATURES 2

#define TRAIN_SIZE 80
#define TEST_SIZE 20
void train_data(float data[ROWS][COLS], float train_X[TRAIN_SIZE][FEATURES], float train_y[TRAIN_SIZE]);

#endif
