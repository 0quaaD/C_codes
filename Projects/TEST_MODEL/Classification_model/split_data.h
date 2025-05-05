#ifndef SPLIT_DATA_H
#define SPLIT_DATA_H

#define ROWS 100
#define COLS 3
#define NUM_FEATURES 2

#define TRAIN_SIZE 80
#define TEST_SIZE 20

#define ORIGINAL_FEATURES 2
#define CAT_FEATURES 2
#define FINAL_FEATURES (1 + CAT_FEATURES)

void data_split(float data[ROWS][COLS]);
float** data_split_X(float data[ROWS][COLS]);
float* data_split_y(float data[ROWS][COLS]);
void checkNull(float data[ROWS][COLS]);

float** train_X_data(float data[ROWS][COLS]);
float* train_y_data(float data[ROWS][COLS]);
float** test_X_data(float data[ROWS][COLS]);
float* test_y_data(float data[ROWS][COLS]);

void free_2d_arr(float** arr, int rows);
void free_model_mem(float* z, float* pred);
#endif
