#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomNum(int min,int max, int count){
	
	srand(time(NULL));
	int number;
	for(int i=0;i<=count;i++){
		number = rand()%(max-min+1)+min;
	}
	return number;
}
int guessNum(int Min, int Max, int Count){
	srand(time(NULL));
	int num;
	for(int i=0;i<Count;i++) num = rand()%(Max-Min+1)+Min;
	return num;
}
void printMesg(){
	printf("Welcome to the guessing game.\n");
	printf("In that game, you, user will try to find hidden number.\nMaybe you should begin, shouldn't we?\n");
	printf("By the way, the number will be in this range: 0 <-> 1000\n");
	printf("In the game, you will have number of guesses which is the number will be given randomly every time.\n");
	printf("Good Luck!\n");
}
int main(){

	int comp_num, user_input, num_count = 1, Min=5, Max=20, Count=1;
	int min=0, max = 1000, user_guesses;
	int flag = 0, guesses = 0;;
	printMesg();
	
	comp_num = randomNum(min,max,num_count);
	user_guesses = guessNum(Min,Max,Count);

	if(user_guesses >=7) printf("You have a very good luck :D. You have %d guesses. Use carefully :)\n",user_guesses);
	else printf("Oops -_- ... You are a lucky person maybed -_* \n");

	for(int i=0; i< user_guesses; i++){
		printf("Now enter a number to check: ");
		scanf("%d",&user_input);
		if(user_input < comp_num) {
			printf("Maybe you should consider higher number than %d.\n",user_input);
			
		}
		else if (user_input > comp_num) printf("Oops, think a bit smaller number than %d.\n",user_input);
		else {
			flag = 1;
			break;
		}
		guesses+=1;
	}
	if (flag == 1) printf("Congratulations!!! You found the number within guesses. And you used %d guesses\n",guesses+1);
	else printf("Don't be sad. Maybe next time you can find the number -_- By the way, you used all of your guesses.\n");
	return 0;
}
