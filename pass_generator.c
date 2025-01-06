#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void passGenerate(int size){
	char num[] = "0123456789";
	char smallChar[] = "abcdefghijklmnopqrstuvxwyz";
	char bigChar[] = "ABCDEFGHIJKLMNOPQRSTUVXWYZ";
	char specialChar[] = "!@#$%,.{}()[]^&*-=+/_";
	int randomizer = 0;
	srand(time(NULL));
	char finalPass[size] = {}; 

	randomizer = rand() % 4;

	for(int i=0;i<size;i++){
		if(randomizer == 1){
			finalPass[i] = specialChar[rand() % 22];
			randomizer = rand() % 4;
		}
		else if(randomizer == 2){
			finalPass[i] = num[rand() % 10];
			randomizer = rand() % 4;
		}
		else if(randomizer == 3){
			finalPass[i] = bigChar[rand() % 26];
			randomizer = rand() % 4;
		}
		else{
			finalPass[i] = smallChar[rand() % 26];
			randomizer = rand() % 4;
		}
	}
	
	for(int i=0; i<sizeof(finalPass) / sizeof(finalPass[0]); i++){
		printf("%c",finalPass[i]);
	}
	/*int count = 0;
	for(int i=0;i<sizeof(specialChars) / sizeof(specialChars[0]);i++) count++;
	printf("Number of symbols: %d\n",count);*/
	
}	

int main(){
	int passLength;
	printf("Enter the size of password: ");
	scanf("%d",&passLength);
	if(passLength >= 12){
		printf("Your password is: ");
		passGenerate(passLength);
		printf("\n");
	}
	else{
		printf("Your password will not be strong enough. Please enter the length at least 12.\n");
	}
	return 0;
}
