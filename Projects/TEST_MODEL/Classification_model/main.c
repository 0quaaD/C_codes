#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "split_data.h"

#define NUM_SAMPLES 5
#define NUM_CLASSES 2
#define ORIGINAL_FEATURES 2
#define CAT_FEATURES 2
#define FINAL_FEATURES (1 + CAT_FEATURES)

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

int main(void)
{
    srand(time(NULL));
    float w1 = rand_float_gen() * 2.0f - 1.0f;
    float w2 = rand_float_gen() * 2.0f - 1.0f;
    float b = rand_float_gen() * 2.0f - 1.0f;
    printf("w1 = %.4f, w2 = %.4f, b = %.4f\n\n\n",w1,w2,b);

    //int one_hot_y[NUM_SAMPLES][NUM_CLASSES] = {0};
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
        printf("%.1f ",data_y[i]);
    }
    cleanMem(data_X, data_y, y_encoded, X_encoded);
    return 0;
}
