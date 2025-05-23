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
   // printf("test_X --> min : %.1f, max : %.1f\n",min,max);

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

void test_X_encoded(float test_X[TEST_SIZE][FEATURES], float test_X_encode[TEST_SIZE][FEATURES]){
    for(int i=0;i<TEST_SIZE;i++){
        int cat = (int)test_X[i][1];
        test_X_encode[i][0] = 0.0f;
        test_X_encode[i][1] = 0.0f;
        if(cat >= 0.0f && cat < CAT_FEATURES) test_X_encode[i][cat] = 1.0f;
        else printf("Unexpected value appeared at row %d : value --> %.1f\n",i,test_X[i][1]);
    }

}

void test_X_final(float test_X_sc[TEST_SIZE], float test_X_encode[TEST_SIZE][FEATURES], float test_X_final_[TEST_SIZE][FINAL_FEATURES]){
    for(int i=0;i<TEST_SIZE;i++){
        test_X_final_[i][0] = test_X_sc[i]; 
        for(int j=0;j<FEATURES;j++){
            test_X_final_[i][j+1] = test_X_encode[i][j];

        }
    }
}

void compute_z_test(float test_X_final_[TEST_SIZE][FINAL_FEATURES], float w[FINAL_FEATURES], float* b, float test_z[TEST_SIZE]){
    for(int i=0;i<TEST_SIZE;i++){
        for(int j=0;j<FINAL_FEATURES;j++){
            test_z[i] += (test_X_final_[i][j] * w[j]);
        }
        test_z[i] += *b;
    }
    
}
float relu(float x){
    return (x > 0) ? x : 0;
}
void test_preds(float test_z[TEST_SIZE], float test_pred[TEST_SIZE]){
    for(int i=0;i<TEST_SIZE;i++){
        test_pred[i] = relu(test_z[i]);
    }
}

float acc_test(float test_y_encode[TEST_SIZE][FEATURES], float test_pred[TEST_SIZE]){
    float test_ac = 0.0f;
    int test_corr = 0.0f;
    for(int i=0;i<TEST_SIZE;i++){
        int pred_cls = (test_pred[i] >= 0.5) ? 1 : 0;
        int act_cls = (test_y_encode[i][1] == 1.0f) ? 1 : 0;
        if(pred_cls == act_cls) test_corr++;
    }

    test_ac = (float)test_corr / TEST_SIZE;
    return test_ac;
}
