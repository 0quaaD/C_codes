#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
float f(float x){
	return 1.f/ (1.f + expf(-x));
}
float train_or[][3] = {
	{0,0,0},
	{0,1,1},
	{1,0,1},
	{1,1,1},
};
float train_and[][3] = {
	{0,0,0},
	{0,1,0},
	{1,0,0},
	{1,1,1},
};
#define train_count_or (sizeof(train_or)/sizeof(train_or[0]))
#define train_count_and (sizeof(train_and) / sizeof(train_and[0]))
float rand_float(void){
	return (float)rand() / (float)RAND_MAX;
}

float cost(int choice, float w1, float w2, float b){
	float res = 0.0f;
	if(choice == 1){
		for(size_t i=0;i<train_count_and;++i){
			float x1 = train_and[i][0], x2 = train_and[i][1];
			float y = f(x1* w1+ x2*w2+b);
			float d = y - train_and[i][2];
			res += d*d;
		}
		res /= train_count_and;
	}
	else if(choice == 2){
		for(size_t i = 0; i < train_count_or;++i){
			float x1 = train_or[i][0], x2 = train_or[i][1];
			float y = f(x1*w1 + x2*w2 + b);
			float d = y - train_and[i][2];
			res += d*d;
		}
	}
	return res;
}

float training(int choice,float w1,float w2,float b,float eps,float rate,long int size){
	for(size_t i=0;i<size;++i){
		float c = cost(choice,w1,w2,b);
	//	printf("%zu: w1 = %f, w2 = %f, cost = %f, b = %f\n",i+1,w1,w2,c,b);
		float dw1 = (cost(choice,w1+eps,w2,b) - c)/eps;
		float dw2 = (cost(choice,w1,w2+eps,b) - c)/eps;
		float db = (cost(choice,w1,w2,b+eps) - c)/eps;

		w1 -= rate*dw1; w2 -= rate*dw2; b -= rate * db;
	}
	return w1, w2, b;

}
int main(void){
	srand(time(NULL));
	long int a = 10*10*10*10*10*10;
	float w1 = rand_float(), w2 = rand_float(), b = rand_float() * 2.0 - 1.0;
	float eps = 1e-2, rate = 1e-1;

	printf("Want to see the AND(1) or OR(2) gate model: ");
	printf("\n");

	int choice;
	scanf("%d",&choice);

	if(choice == 1) puts("---------- AND GATE ----------");
	else if(choice == 2) puts("------------ OR GATE -----------");
	else printf("Choose 1 or 2 next time!\n");
	
	float trained_model = training(choice,w1,w2,b,eps,rate,a);
	printf("w1 = %f, w2 = %f, cost = %f,b = %f\n",w1,w2,cost(choice,w1,w2,b),b);	
	double threshold = 0.5;
	int corr_values = 0;
	int expected_values_and[4] = {0,0,0,1};
	int expected_values_or[4] = {0,1,1,1};
	for(size_t i=0;i<2;++i){
		for(size_t j=0;j<2;++j){
			double prediction = f(i*w1 + j*w2 + b);
			printf("%zu | %zu = %f\n",i,j,prediction);
			int binary_output = prediction >= threshold ? 1 : 0;
			
			if(choice == 1){
				int expected = expected_values_and[i*2+j];
				if(binary_output == expected)  corr_values += 1;
			}
			else{
				int expected = expected_values_or[i*2+j];
				if(binary_output == expected) corr_values += 1;
			}
		}
	}
	double accuracy = (corr_values / 4.0) * 100.0;
	printf("Accuracy : %.2f%%\nThreshold = %.2f\n",accuracy,threshold);	
	puts("-----------------------");
	return 0;
}
