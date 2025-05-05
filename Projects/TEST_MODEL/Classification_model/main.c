#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "split_data.h"


#define ROWS 100
#define NUM_CLASSES 2
void cleanMem(float** data_X, float* data_y, float** y_encoded, float** X_encoded,float* w, float** X_scaled, float** train_X, float* train_y, float** test_X, float* test_y){
    free_2d_arr(data_X, ROWS);
    free(data_X);

    free(data_y);

    free_2d_arr(y_encoded, ROWS);
    free(y_encoded);

    free_2d_arr(X_encoded, ROWS);
    free(X_encoded);
    
    free(w);

    free_2d_arr(X_scaled, ROWS);
    free(X_scaled);

    free_2d_arr(train_X, TRAIN_SIZE);
    free(train_X);

    free(train_y);

    free_2d_arr(test_X, TEST_SIZE);
    free(test_X);

    free(test_y);

}


float df[ROWS][COLS] = {
    {140.0f, 0.0f, 0.0f}, {130.0f, 0.0f, 0.0f}, {150.0f, 1.0f, 1.0f}, {170.0f, 1.0f, 1.0f}, 
    {120.0f, 0.0f, 0.0f}, {135.0f, 0.0f, 0.0f}, {160.0f, 1.0f, 1.0f}, {180.0f, 1.0f, 1.0f}, 
    {110.0f, 0.0f, 0.0f}, {125.0f, 0.0f, 0.0f}, {145.0f, 0.0f, 0.0f}, {155.0f, 1.0f, 1.0f}, 
    {175.0f, 1.0f, 1.0f}, {115.0f, 0.0f, 0.0f}, {132.0f, 0.0f, 0.0f}, {162.0f, 1.0f, 1.0f}, 
    {185.0f, 1.0f, 1.0f}, {105.0f, 0.0f, 0.0f}, {128.0f, 0.0f, 0.0f}, {148.0f, 0.0f, 0.0f},
    {158.0f, 1.0f, 1.0f}, {178.0f, 1.0f, 1.0f}, {118.0f, 0.0f, 0.0f}, {138.0f, 0.0f, 0.0f}, 
    {168.0f, 1.0f, 1.0f}, {188.0f, 1.0f, 1.0f}, {108.0f, 0.0f, 0.0f}, {133.0f, 0.0f, 0.0f}, 
    {153.0f, 1.0f, 1.0f}, {173.0f, 1.0f, 1.0f}, {123.0f, 0.0f, 0.0f}, {143.0f, 0.0f, 0.0f}, 
    {163.0f, 1.0f, 1.0f}, {183.0f, 1.0f, 1.0f}, {113.0f, 0.0f, 0.0f}, {137.0f, 0.0f, 0.0f}, 
    {157.0f, 1.0f, 1.0f}, {177.0f, 1.0f, 1.0f}, {117.0f, 0.0f, 0.0f}, {127.0f, 0.0f, 0.0f},
    {147.0f, 0.0f, 0.0f}, {167.0f, 1.0f, 1.0f}, {187.0f, 1.0f, 1.0f}, {107.0f, 0.0f, 0.0f}, 
    {129.0f, 0.0f, 0.0f}, {149.0f, 0.0f, 0.0f}, {159.0f, 1.0f, 1.0f}, {179.0f, 1.0f, 1.0f}, 
    {119.0f, 0.0f, 0.0f}, {139.0f, 0.0f, 0.0f}, {169.0f, 1.0f, 1.0f}, {189.0f, 1.0f, 1.0f}, 
    {109.0f, 0.0f, 0.0f}, {134.0f, 0.0f, 0.0f}, {154.0f, 1.0f, 1.0f}, {174.0f, 1.0f, 1.0f}, 
    {124.0f, 0.0f, 0.0f}, {144.0f, 0.0f, 0.0f}, {164.0f, 1.0f, 1.0f}, {184.0f, 1.0f, 1.0f},
    {114.0f, 0.0f, 0.0f}, {136.0f, 0.0f, 0.0f}, {156.0f, 1.0f, 1.0f}, {176.0f, 1.0f, 1.0f}, 
    {116.0f, 0.0f, 0.0f}, {126.0f, 0.0f, 0.0f}, {146.0f, 0.0f, 0.0f}, {166.0f, 1.0f, 1.0f}, 
    {186.0f, 1.0f, 1.0f}, {106.0f, 0.0f, 0.0f}, {131.0f, 0.0f, 0.0f}, {151.0f, 1.0f, 1.0f}, 
    {171.0f, 1.0f, 1.0f}, {121.0f, 0.0f, 0.0f}, {141.0f, 0.0f, 0.0f}, {161.0f, 1.0f, 1.0f}, 
    {181.0f, 1.0f, 1.0f}, {111.0f, 0.0f, 0.0f}, {126.0f, 0.0f, 0.0f}, {152.0f, 1.0f, 1.0f},
    {172.0f, 1.0f, 1.0f}, {122.0f, 0.0f, 0.0f}, {142.0f, 0.0f, 0.0f}, {165.0f, 1.0f, 1.0f}, 
    {182.0f, 1.0f, 1.0f}, {112.0f, 0.0f, 0.0f}, {132.0f, 0.0f, 0.0f}, {150.0f, 1.0f, 1.0f}, 
    {170.0f, 1.0f, 1.0f}, {120.0f, 0.0f, 0.0f}, {140.0f, 0.0f, 0.0f}, {160.0f, 1.0f, 1.0f}, 
    {180.0f, 1.0f, 1.0f}, {110.0f, 0.0f, 0.0f}, {124.0f, 0.0f, 0.0f}, {144.0f, 0.0f, 0.0f}, 
    {168.0f, 1.0f, 1.0f}, {190.0f, 1.0f, 1.0f}, {104.0f, 0.0f, 0.0f}, {138.0f, 0.0f, 0.0f}, 
};

float rand_float_gen(void){
    return (float)rand() / (float)RAND_MAX;
}

float sigmoid_f(float x){
    return 1.0f / (1.0f + expf(-x));
}

float** encode_y(float* y){
    float** one_hot = (float**)malloc(TRAIN_SIZE * sizeof(float*));
    if(!one_hot){
        fprintf(stderr, "Encode_y one_hot array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<ROWS;i++){
        one_hot[i] = (float*)calloc(NUM_CLASSES, sizeof(float));
        if(!one_hot[i]){
            fprintf(stderr, "Encode_y one_hot[i] array allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        int class_index = (int)y[i];

        if(class_index >= 0.0f && class_index < NUM_CLASSES)
            one_hot[i][class_index] = 1.0f;
        else
            printf("Invalid class index at row %d : %.1f\n",i,y[i]);
    }
    return one_hot;
}

float** encode_X(float** X){
    float** one_hot_x = (float**)malloc(TRAIN_SIZE * sizeof(float*));
    if(!one_hot_x){
        fprintf(stderr, "Encode_X one_hot_x array allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<ROWS;++i){
        one_hot_x[i] = (float*)calloc(FINAL_FEATURES, sizeof(float));
        if(!one_hot_x[i]){
            fprintf(stderr, "Encoded_X one_hot_x[i] array allocation failed!\n");
            exit(EXIT_FAILURE);
        } 

        one_hot_x[i][0] = X[i][0];

        int cat = (int)X[i][1];
        if(cat >= 0 && cat < CAT_FEATURES){
            one_hot_x[i][cat+1] = 1.0f;
        }
        else printf("Invalid category value at row %d: %.1f\n",i,X[i][1]);
    }

    return one_hot_x;

}


float* weights_(void){
    float* weights = (float*)malloc(FINAL_FEATURES * sizeof(float));
    if(!weights){
        fprintf(stderr, "Weights array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i< FINAL_FEATURES; i++){
        weights[i] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    }
    return weights;
}

float* compute_z(float** X, float* w, float b){
    float* z = (float*)malloc(ROWS * sizeof(float));
    if(!z){
        fprintf(stderr, "Z array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<ROWS;i++){
        z[i] = 0.0f;
        for(int j=0;j<FINAL_FEATURES;j++){
            z[i] += (X[i][j] * w[j]);
        }
        z[i] += b;
    }
    return z;
    
}
float* preds(float* z){
   
    float* pred = (float*)malloc(ROWS * sizeof(float));
    if(!pred){
        fprintf(stderr, "Preds array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<ROWS;i++){
        pred[i] = sigmoid_f(z[i]);
    }
    return pred;
}

float** scaling(float** X){
    float min = X[0][0], max = X[0][0];
    for(int i=1;i<ROWS;i++){
        if(X[i][0] < min) min = X[i][0];
        if(X[i][0] > max) max = X[i][0];
    }
    
    
    

    float** X_scaled =  (float**)malloc(ROWS * sizeof(float*));
    if(!X_scaled){
        fprintf(stderr, "X_scaled array allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<ROWS;i++){ 
        X_scaled[i] = (float*)malloc(FINAL_FEATURES * sizeof(float));
        if(!X_scaled[i]){
            fprintf(stderr, "X_scaled[i] array allocation failed!\n");
            exit(EXIT_FAILURE);
        }
    

        X_scaled[i][0] = (X[i][0] - min) / (max - min);
        
        // Copy the one-hot encoded features
        for(int j = 1; j < FINAL_FEATURES; j++) {
            X_scaled[i][j] = X[i][j];
        }

    }
    return X_scaled;
}

float cost(float** y, float* pred){
    float res = 0.0f;
    for(int i=0;i<ROWS;i++){
        float yi = y[i][0];
        if(pred[i] <= 0.0f) pred[i] = 1e-10f;
        if(pred[i] >= 1.0f) pred[i] = 1.0f - 1e-10f;

        res += (*(y[i]) * logf(pred[i])+(1 - *(y[i])) * logf(1 - pred[i]));
    }
    res /= -ROWS;
    return res;

}

void gradient_descent(float* w, float** X, float** y, float* p, float* dw_out, float* db_out){
    for(int i=0;i<FINAL_FEATURES;i++){
        dw_out[i] = 0.0f;
    }
    *db_out =0.0f;

    for(int i=0;i<ROWS;i++){
        float error = (p[i] - y[i][0]);
        for(int j=0;j<FINAL_FEATURES;j++){
            dw_out[j] += error * X[i][j]; 
        }
        *db_out += error;
    }
    for(int i=0;i<FINAL_FEATURES;i++){
        dw_out[i] /= ROWS;
    }
    *db_out /= ROWS;
        
    
}
int main(void){
    srand(time(NULL));
   
    float* w = weights_();
    float bias = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    checkNull(df);
    float* data_y = data_split_y(df);
    float** data_X = data_split_X(df);


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("data_X[%d][%d] = %f\n", i, j, data_X[i][j]);
        }
        printf("data_y[%d] = %f\n", i, data_y[i]);
    }

    float** train_X = train_X_data(df);
    float** test_X = test_X_data(df);
    float* train_y = train_y_data(df);
    float* test_y = test_y_data(df);

    float** X_encoded = encode_X(data_X);
    float** y_encoded = encode_y(data_y);

    float** X_scaled = scaling(X_encoded);
    

    float dw[FINAL_FEATURES] = {0};
    float db = 0.0f;
    float lr = 0.01f;
    
    int iterations = 1000;
    for(int i=0;i<iterations;i++){
        if(i % 100 == 0) printf("Iteration: %dth iteration\n",i);
        float* z = compute_z(X_scaled, w, bias);
        float* pred = preds(z);
        float loss = cost(y_encoded, pred);
        gradient_descent(w,X_scaled,y_encoded,pred,dw,&db);
        for(int i=0;i<FINAL_FEATURES;i++){
            w[i] -= lr * dw[i]; 
        }
        bias -= lr * db;
        free_model_mem(z,pred); 
    }
    float* z = compute_z(X_scaled, w, bias);
    float* pred = preds(z);
    float loss = cost(y_encoded, pred);
    printf("Loss = %.4f\n",loss);
    for(int i=0;i<ROWS;i++){
        printf("preds[%d] --> %.4f\n",i,pred[i]);
    }
    int correct = 0;
    for(int i=0;i<ROWS;i++){
        int pred_cls = (pred[i] >= 0.5) ? 1 : 0;
        int act_cls = (int)(*(y_encoded[i]));
        if(pred_cls == act_cls){
            correct++;
        }

    }
    float acc = (float)correct / ROWS;
    printf("Accuracy : %.2f%%\n",100 * acc);
    for(int i=0;i<ROWS;i++) printf("%.4f\n",*(y_encoded[i]));
    
    free(z); 
    free(pred);
    cleanMem(data_X, data_y, y_encoded, X_encoded,w,X_scaled,train_X,train_y,test_X,test_y);
    return 0;
}
