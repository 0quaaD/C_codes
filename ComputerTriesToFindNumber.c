
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long
int main(){
	int found=0;
	ll computer_guess,guesses;
	char user_input[20];
	printf("Please select in your mind a number in the range--> [0 <-> 1000000]\n");
	printf("Tell the number of guesses the computer will try to find the correct number.\n");
	printf("Enter the guesses the computer should try to find the number: ");
	scanf("%lld",&guesses);
	ll used = 0;
	ll low,mid,high;
	low = 0; high = 1000000;
	for(ll i=0;i<guesses;i++){
		mid = (low+high)/2;
		computer_guess = mid;
		printf("Is your number 'higher', 'lower', or 'correct' relative to %lld? -- ", computer_guess);
		scanf("%s",user_input);
		printf("\n");
		used++;
		if (strcmp(user_input,"higher") == 0){
			printf("Number is between %lld and %lld.\n",mid+1,high);
			low = mid + 1;
		}
		else if(strcmp(user_input,"lower") == 0){
			printf("Number is between %lld and %lld.\n",low,mid-1);
			high = mid - 1;
		}
		else if(strcmp(user_input,"correct") == 0){
			found = 1;
			break;
		}
		else{
			printf("Invalid input. Enter the given values above.\n");
			i--;
			continue;
		}
	}
	if(found) printf("Your number is: %lld and the computer used %lld guesses to find it\n",computer_guess,used);
	else printf("Computer couldn't find the number with given guesses -_-\n");
	return 0;
}
