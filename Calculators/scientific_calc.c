#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
void message(){

	printf("\n============= Scientific Calculator ================\n");
	printf("Enter your choice:\n");
	printf("1. sin\n2. cos\n3. tan\n4. square root\n");
	printf("5. addition\n6. subtraction\n7. multiplication\n8. division");
	printf("\n9. natural log (ln)\n10. log base 2(log_2)\n11. log based any number(log_n)\n");
	printf("12. Power(x^y)\n13. Exponential (e^x)\n14. Cube root\n15. Nth degree root\n");
	printf("16. Absolute Value\n17. Modulus\n18. Ceil\n19. Floor\n20. Round\n21. Exit");
}
int main(void){
	int choice;
	double num1,num2,res;
	do{
		message();
		printf("\nEnter your choice (1-21): ");
		scanf("%d",&choice);
		if((choice >= 1 && choice <=4) || choice == 9 || choice == 10 || choice == 13 || choice == 14 || choice == 16 || (choice >= 18 && choice <= 20)){
			printf("Enter 1 value: ");
			scanf("%le",&num1);
		}
		else if((choice >= 5 && choice <= 8) || choice == 11 || choice == 12 || choice == 15 || choice == 17){
			printf("Enter 2 values: ");
			scanf("%le %le",&num1,&num2);
		}

		switch(choice){
			case 1: res = sin(num1 * M_PI / 180); break;
			case 2: res = cos(num1 * M_PI / 180); break;
			case 3: res = tan(num1 * M_PI / 180); break;
			case 4: res = sqrt(num1); break;
			case 5: res = num1 + num2; break;
			case 6: res = num1 - num2; break;
			case 7: res = num1 * num2; break;
			if(num2 != 0){case 8: res = num1 / num2; break;}
			else {printf("Can't divide to 0 !\n"); return 1;}
			case 9: res = log(num1); break;
			case 10: res = log2(num1); break;
			case 11: res = log(num1) / log(num2); break;
			case 12: res = pow(num1,num2); break;
			case 13: res = exp(num1); break;
			case 14: res = cbrt(num1); break;
			case 15: res = pow(num1, 1.0/num2); break;
			case 16: res = fabs(num1); break;
			case 17: res = fmod(num1,num2); break;
			case 18: res = ceil(num1); break;
			case 19: res = floor(num1); break;
			case 20: res = round(num1); break;
			case 21: printf("Program ends.\n"); return 0;
			default:
				 printf("invalid choice!\n");
				 return 0;
		}
		printf("Result is: %.4f\n",res);
	}
	while(1);
	return 0;
}
