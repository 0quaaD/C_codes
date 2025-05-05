#ifndef SPLIT_DATA_H
#define SPLIT_DATA_H

#define ROWS 5
#define COLS 3
#define NUM_FEATURES COLS-1

#define ORIGINAL_FEATURES 2
#define CAT_FEATURES 2
#define FINAL_FEATURES (1 + CAT_FEATURES)

void data_split(float data[ROWS][COLS]);
float** data_split_X(float data[ROWS][COLS]);
float* data_split_y(float data[ROWS][COLS]);
void checkNull(float data[ROWS][COLS]);


#endif
