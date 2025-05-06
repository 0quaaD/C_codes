#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "training.h"
#include "testing.h"

#define CAT_FEATURES_X 2
#define FINAL_FEATURES_X  1+CAT_FEATURES_X

#define CAT_FEATURES_Y 2
#define FINAL_FEATURES_Y 1+CAT_FEATURES_Y

#define ROWS 100
#define COLS 3

#define TRAIN_SIZE 80
#define TEST_SIZE 20

float data[][3] = {
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

float sigmoid_f(float x){
    float s = 1.0f / (1.0f + expf(-x));
    if(s < 1e-7f) s = 1e-7f;
    if(s > 1e-7f) s = 1.0f - 1e-7f;
    return s;
}
float relu_f(float x){
    return x>0 ? x : 0;
}

float rand_float(void){
    return ((float)rand() / (float)RAND_MAX - 0.5f) * 1.0f;
}
void generate_w(float w[3]){
    // generating W
    for(int i=0;i<3;i++){
       
        w[i] = rand_float();
    }
}
void one_hot_X(float train_X[TRAIN_SIZE][2], float one_hot_X_[TRAIN_SIZE][2]){
    for(int i=0;i<TRAIN_SIZE;i++){
        int cat1 = (int)train_X[i][1];
        one_hot_X_[i][0] = 0.0f;
        one_hot_X_[i][1] = 0.0f;
        if(cat1 >= 0.0f && cat1 < 2){
            one_hot_X_[i][cat1] = 1.0f;
        }
        else printf("Unexpected value appeared at row %d --> value : %f\n",i, train_X[i][1]);
    }
}
void one_hot_y(float train_y[TRAIN_SIZE],float one_hot_y_[TRAIN_SIZE][2]){
    // Encoding for train_y
    // it should becomes like this
    // [1,0],
    // [0,1]
    // because it has 2 values -> 1 and 0
    for(int i=0;i<TRAIN_SIZE;i++){
        int cat = (int)train_y[i];
        for(int j=0;j<FINAL_FEATURES_Y - 1;j++){
            one_hot_y_[i][j] = (j == cat) ? 1.0f : 0.0f;
        } 
    }
}
void scaled(float train_X[TRAIN_SIZE][2], float one_hot_X_[TRAIN_SIZE][2], float train_X_final[TRAIN_SIZE][3], float scaled_X[TRAIN_SIZE]){
    
    float min = train_X[0][0], max = train_X[0][0];
    for(int i=0;i<TRAIN_SIZE;i++){
        if(train_X[i][0] < min) min = train_X[i][0];
        if(train_X[i][0] > max) max = train_X[i][0];
    }
  
    float range = max - min;
    if(range == 0) {
        perror("Cannot be scaled!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<TRAIN_SIZE;i++){
        scaled_X[i] = ((train_X[i][0] - min) / range);
    }
    
    
    for(int i=0;i<TRAIN_SIZE;i++){
        train_X_final[i][0] = scaled_X[i];
        for(int j=0;j<2;j++){
            train_X_final[i][j+1] = one_hot_X_[i][j];
        }
    }
}
void checkNull(float z[TRAIN_SIZE], float pred[TRAIN_SIZE]){
    for(int i=0;i<TRAIN_SIZE;i++){
        if(isnan(z[i]) || isnan(pred[i])){
            perror("Z or PRED is NULL!\n");
            exit(1);
        }
    }
}
void compute_z(float train_X_final[TRAIN_SIZE][3],float w[3], float *b, float z[TRAIN_SIZE]){
    // Compute z = W*X + b
    for(int i=0;i<TRAIN_SIZE;i++) z[i] = 0.0f;
    for(int i=0;i<TRAIN_SIZE;i++){
        for(int j=0;j<3;j++)
            z[i] += (train_X_final[i][j] * w[j]);
    
        z[i] += *b;
    }
}
void preds(float z[TRAIN_SIZE], float pred[TRAIN_SIZE]){
    // Predict some values
    for(int i=0;i<TRAIN_SIZE;i++){
        pred[i] = relu_f(z[i]);
    }
}
void cost(float train_y[TRAIN_SIZE], float pred[TRAIN_SIZE]){
    // Calculate cost
    float loss = 0.0f;
    for(int i=0;i<TRAIN_SIZE;i++){
        if(pred[i] <= 0.0f) pred[i] = 1e-7f;
        if(pred[i] >= 1.0f) pred[i] = 1.0f - 1e-7f;

        loss += (train_y[i] * logf(pred[i]) + (1-train_y[i]) * logf(1-pred[i]));
        
    }
    loss /= -TRAIN_SIZE;
    if(isnan(loss)){
        perror("Loss is NAN! --> ");
        exit(1);
    }
   // printf("Loss : %.12f\n",loss);
    
}
void grad_desc(float train_X_final[TRAIN_SIZE][3], float train_y[TRAIN_SIZE], float pred[TRAIN_SIZE],float w[3], float* b){
    // Calculate gradient descent
    float lr = 0.001f;
    float dw[3] = {0.0f}, db = 0.0f;
    for(int i=0;i<TRAIN_SIZE;i++){
        float error = pred[i]  - train_y[i];
        for(int j=0;j<3;j++){
            dw[j] += error * train_X_final[i][j];
        }
        db += error;
    }
    for(int i=0;i<3;i++){
        dw[i] /=  TRAIN_SIZE;
        w[i] -= lr * dw[i];
    }
    db /= 3;
    *b -= lr * db;
}


int main(void){
    srand(time(NULL));
    float train_X[TRAIN_SIZE][FEATURES], train_y[TRAIN_SIZE];
    train_data(data, train_X, train_y);
    
    float w[3], one_hot_X_[TRAIN_SIZE][2], one_hot_y_[TRAIN_SIZE][2], train_X_final[TRAIN_SIZE][3];
    generate_w(w);
    float b = rand_float(), z[TRAIN_SIZE], pred[TRAIN_SIZE], scaled_X[TRAIN_SIZE];
    one_hot_X(train_X,one_hot_X_);
    one_hot_y(train_y, one_hot_y_);


    scaled(train_X, one_hot_X_, train_X_final, scaled_X);
    checkNull(z,pred);
    int iter = (int)1e+5;
    for(int i=0;i<iter;i++){
        
       // printf("ITERATION %d: ",i);
        compute_z(train_X_final,w,&b,z);
        preds(z,pred);
        cost(train_y, pred);
        grad_desc(train_X_final, train_y, pred,w,&b);
        //printf("\n");
    }
    float acc = 0.0f;
    int corr = 0;
    for(int i=0;i<TRAIN_SIZE;i++){
        int pred_cls = (pred[i] >= 0.5) ? 1 : 0;
        int act_cls = (int)(train_y[i]);
        if(pred_cls == act_cls) corr++; 
    }
    acc = (float)corr / TRAIN_SIZE;
    printf("Training data accuracy : %.2f%%\n",100 * acc);

    float test_X[TEST_SIZE][FEATURES], test_y[TEST_SIZE];
    test_data(data, test_X, test_y);
    /*printf("\nTest X data:\n");
    for(int i=0;i<TEST_SIZE;i++){
        for(int j=0;j<FEATURES;j++) printf("%.1f ",test_X[i][j]);
        printf("\n");
    }
    printf("\nTest y data:\n");
    for(int i=0;i<TEST_SIZE;i++){
        printf("%.1f\n",test_y[i]);
    }*/
    
    float test_y_encode[TEST_SIZE][FEATURES];
    test_y_encoded(test_y, test_y_encode); puts("");
    /*printf("Test_y encoded:\n");
    for(int i=0;i<TEST_SIZE;i++){
        for(int j=0;j<FEATURES;j++) printf("%.1f ",test_y_encode[i][j]);
        printf("\n");
    }*/
    float test_X_sc[TEST_SIZE];
    test_X_scaled(test_X,test_X_sc);
    printf("\nTEST_X SCALED:\n");
    for(int i=0;i<TEST_SIZE;i++) printf("%.1f\n",test_X_sc[i]);
    

    float test_X_encode[TEST_SIZE][FEATURES];
    test_X_encoded(test_X,test_X_encode);
    printf("\nTEST_X ENCODED\n");
    for(int i=0;i<TEST_SIZE;i++){
        for(int j=0;j<FEATURES;j++) printf("%.1f ",test_X_encode[i][j]);
        printf("\n");
    }
    
    
    float test_X_final_[TEST_SIZE][FINAL_FEATURES];
    printf("\nSCALED AND ENCODED TEST_X:\n");
    for(int i=0;i<TEST_SIZE;i++){
        for(int j=0;j<FINAL_FEATURES;j++) printf("%.1f ",test_X_final_[i][j]);
        printf("\n");
    }
    return 0;
}
