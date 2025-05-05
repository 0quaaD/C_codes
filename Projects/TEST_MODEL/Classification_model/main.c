#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "split_data.h"

#define NUM_SAMPLES 5
#define NUM_CLASSES 2
void cleanMem(float** data_X, float* data_y, float** y_encoded, float** X_encoded){
    for(int i=0;i<ROWS;i++) free(data_X[i]);
    free(data_X);

    free(data_y);

    for(int i=0;i<ROWS;i++) free(y_encoded[i]);
    free(y_encoded);

    for(int i=0;i<ROWS;i++) free(X_encoded[i]);
    free(X_encoded);

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
    return 1.0f / (1.0f + exp(-x));
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


void weights_and_bias(void){
    float* weights = (float*)malloc(NUM_SAMPLES * sizeof(float));
    float bias = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    for(int i=0;i< NUM_SAMPLES; i++){
        weights[i] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    }
    for(int i=0;i<NUM_SAMPLES;i++){
        printf("w[%d] = %.4f\n",i,weights[i]);
    }
    printf("b = %.4f\n",bias);

    printf("\n\n");
       free(weights);
}
int main(void)
{
    srand(time(NULL));
    weights_and_bias(); 
    float* data_y = data_split_y(df);
    float** data_X = data_split_X(df);

    float** X_encoded = encode_X(data_X);
    float** y_encoded = encode_y(data_y);

    printf("Raw X data:\n");
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;++j){
            printf("%.1f ",data_X[i][j]);
        }
        printf("\n");
    }
    printf("\n\nEncoded X data:\n");

    for(int i=0; i <NUM_SAMPLES;++i){
        for(int j=0;j<FINAL_FEATURES;j++){
            printf("%.1f ",X_encoded[i][j]);
        }
        printf("\n");
    }
   
    printf("\nRaw y data:\n");
    for(int i=0;i<ROWS;i++){
        printf("%.1f\n",data_y[i]);
    }

    printf("\nEndoded y data:\n");
    for(int i=0;i<NUM_SAMPLES;i++){
        for(int j=0;j<NUM_CLASSES;j++){
            printf("%.1f ",y_encoded[i][j]);
        }
        printf("\n");
    }

    //data_split(df);
    cleanMem(data_X, data_y, y_encoded, X_encoded);
    return 0;
}
