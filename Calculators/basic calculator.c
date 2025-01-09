#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(){
	
	int num1,num2,n1,n2,res;
	char op,cont_choice;
	float div_res;
	
	while(true){
	
		printf("enter 1st value: ");
		scanf("%d",&num1);
		printf("enter 2nd value: ");
		scanf("%d",&num2);
	
		getchar();
		printf("\nchoose the operation you want to do: [+,-,*,/] ");
		op = getchar();
		switch(op){
			case '+':
				res = num1+num2;
				break;
			case '-':
				res = num1-num2;
				break;
			case '*':
				res = num1 * num2;
				break;
			case '/':
				if(num2 == 0) printf("can't divide to zero!!!\n");
				else div_res = (float)num1 / num2;
				break;
			default:
				printf("enter the operation from one of 4: +,-,*,/\n");
				break;

		}
		if(op != '/'){
			printf("The result is: %d\n",res);
		}
		else if(op == '/' && num2 == 0) printf("error: can't divide to zero!!!\n");
		else printf("The result is: %.2f\n",div_res);

		getchar();
		printf("want to continue? (y/n): ");
		scanf("%c",&cont_choice);
		printf("\n");
		if (cont_choice == 'n' || cont_choice == 'N'){
			printf("Thank you to use the program.\n");
			break;
		}
	}

	return 0;
}
