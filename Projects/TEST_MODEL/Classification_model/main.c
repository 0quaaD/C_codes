#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "split_data.h"

#define NUM_SAMPLES 5
#define NUM_CLASSES 2
void cleanMem(float** data_X, float* data_y, float** y_encoded, float** X_encoded,float* w, float** X_scaled){
    for(int i=0;i<ROWS;i++) free(data_X[i]);
    free(data_X);

    free(data_y);

    for(int i=0;i<ROWS;i++) free(y_encoded[i]);
    free(y_encoded);

    for(int i=0;i<ROWS;i++) free(X_encoded[i]);
    free(X_encoded);
    
    free(w);

    for(int i=0;i<NUM_SAMPLES;i++) free(X_scaled[i]);
    free(X_scaled);

}

float df[ROWS][COLS] = {
    // COLS(# of samples) --> WEIGHT(GRAMS), TEXTURE(0=SMOOTH,1=BUMPY), LABEL(0=APPLE, 1=ORANGE)
    {140.0f, 0.0f, 0.0f},
    {130.0f, 0.0f, 0.0f},
    {150.0f, 1.0f, 1.0f},
    {170.0f, 1.0f, 1.0f},
    {120.0f, 0.0f, 0.0f},
};

float rand_float_gen(void){
    return (float)rand() / (float)RAND_MAX;
}

float sigmoid_f(float x){
    return 1.0f / (1.0f + expf(-x));
}

float** encode_y(float* y){
    float** one_hot = (float**)malloc(NUM_SAMPLES * sizeof(float*));
    for(int i=0;i<NUM_SAMPLES;i++){
        one_hot[i] = (float*)calloc(NUM_CLASSES, sizeof(float));
        int class_index = (int)y[i];

        if(class_index >= 0.0f && class_index < NUM_CLASSES)
            one_hot[i][class_index] = 1.0f;
        else
            printf("Invalid class index at row %d : %.1f\n",i,y[i]);
    }
    return one_hot;
}

float** encode_X(float** X){
    float** one_hot_x = (float**)malloc(NUM_SAMPLES * sizeof(float*));
    for(int i=0;i<NUM_SAMPLES;++i){
        one_hot_x[i] = (float*)malloc(NUM_SAMPLES * sizeof(float));
        one_hot_x[i][0] = X[i][0];

        int cat = (int)X[i][1];
        for(int j=0;j<CAT_FEATURES;++j){ 
            one_hot_x[i][j+1] = (j==cat) ? 1.0f : 0.0f;
        }
    }
    return one_hot_x;

}


float* weights_(void){
    float* weights = (float*)malloc(NUM_SAMPLES * sizeof(float));
    for(int i=0;i< NUM_SAMPLES; i++){
        weights[i] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    }
    return weights;
}

float* compute_z(float** X, float* w, float b){
    float* z = (float*)malloc(NUM_SAMPLES * sizeof(float));
    for(int i=0;i<NUM_SAMPLES;i++){
        z[i] = 0.0f;
        for(int j=0;j<NUM_FEATURES;j++){
            z[i] += (X[i][j] * w[j]);
        }
        z[i] += b;
    }
    return z;
    
}
float* preds(float* z){
   
    float* pred = (float*)malloc(NUM_SAMPLES * sizeof(float));
    for(int i=0;i<NUM_SAMPLES;i++){
        pred[i] = sigmoid_f(z[i]);
    }
    return pred;
}

float** scaling(float** X){
    float min = X[0][0];
    for(int i=0;i<NUM_SAMPLES;i++){
        
        if(X[i][0] < min){
            float temp = X[i][0];
            // temp , min
            X[i][0] = min;
            min = temp;
        }
    }
    
    float max = X[0][0];
    for(int i=0;i<NUM_SAMPLES;i++){
        if(X[i][0] > max){
            float temp = X[i][0];
            X[i][0] = max;
            max = temp;
        }
    }

    float** X_scaled =  (float**)malloc(NUM_SAMPLES * sizeof(float*));
    for(int i=0;i<NUM_SAMPLES;i++) X_scaled[i] = (float*)malloc(NUM_SAMPLES * sizeof(float));
    for(int i=0;i<NUM_SAMPLES;i++){
        *(X_scaled[i]) = ((X[i][0] - min)/(max-min));
    }

    for(int i=0;i<NUM_SAMPLES;i++){
        X[i][0] = *(X_scaled[i]);
    }

   
    return X_scaled;
}

void cost(float** X, float* y, float* pred){
    printf(" ");
}
int main(void){
    srand(time(NULL));
   
    float* w = weights_();
    float bias = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;

    float* data_y = data_split_y(df);
    float** data_X = data_split_X(df);


    float** X_encoded = encode_X(data_X);
    float** y_encoded = encode_y(data_y);
    float** X_scaled = scaling(X_encoded);
    float* z = compute_z(X_scaled, w, bias);

    float* pred = preds(z);
    printf("Predictions:\n");
    for(int i=0;i<NUM_SAMPLES;i++){
        printf("pred[%d] --> %.1f\n",i,pred[i]);
    }
    
    cleanMem(data_X, data_y, y_encoded, X_encoded,w,X_scaled);
    return 0;
}
