#include "training.h"

void train_data(float data[ROWS][COLS],float train_X[TRAIN_SIZE][FEATURES], float train_y[TRAIN_SIZE]){
    
    for(int i=0;i<TRAIN_SIZE;i++){
        train_y[i] = data[i][FEATURES];
        for(int j=0;j<FEATURES;j++){
            train_X[i][j] = data[i][j];
        }
    }
}
