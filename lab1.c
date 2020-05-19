//Lab 1 Sabiq Khan Tuesday 2:15
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int division(int divisor, int quotient);//declaring the division function

int main(){
	int i, divisor, quotient, checker;
	int counter=0;
	srand((int)time(NULL));
	for(i=0;i<10;i++){ //looping it ten times
		divisor=rand()%12+1;
		quotient=rand()%13; //assigning random values to the variables
		checker=division(divisor,quotient); //calling the function and assigning it to a variable so that i can check the value of the function
		if(checker==1){
			printf("Correct!\n");
			counter++;
		}
		else{
			printf("Wrong. The correct answer is %d\n", quotient);
		}
	}
	printf("You got %d correct\n",counter);
}

int division(int divisor, int quotient){ //bringing in arguments from the main
	int input, dividend;
	dividend=divisor*quotient;
	printf("%d / %d = ?\n", dividend, divisor);
	scanf("%d", &input);
	if(input==quotient){
		return 1;
	}
	else{
		return 0;
	}
}

