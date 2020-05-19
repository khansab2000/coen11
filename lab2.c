//Lab 2 Sabiq Khan Tuesday 2:15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define LENGTH 20 
char names[SIZE][LENGTH];
int size[SIZE];
int counter;
void insert(void);
void removeParty(void);
void list(void);//GLOBAL VARIABLES

int main(void){
	counter=0;
	int input, i;
	for(i=0;i<SIZE;i++){
		names[i][0]='\0';//initializing the names array
	}
	while(1){
		printf("Press 1 to add to the waiting list\n");
		printf("Press 2 to remove someone from the list\n");
		printf("Press 3 to show who is currently waiting\n");
		printf("Press 0 to quit\n");
		scanf("%d", &input);

		switch(input){
			case 1:
				insert();
				break;
			case 2:
				removeParty();
				break;
			case 3:
				list();
				break;
			case 0:
				return 0;
			default:
				printf("Bad option. Pick 1, 2, 3, or 0.\n");
		}
	}
}

void insert(){
	if(counter==SIZE){
		printf("The waiting list is full\n");
	}
	else{
		printf("Name?\n");
		scanf("%s", names[counter]);
		printf("Number of people?\n");
		scanf("%d",&size[counter]);
		counter++;	//scanning in the inputted numbers into the arrays
	}
	return;
}

void removeParty(){
	int removesize, i,j;
	int flag=0;
	printf("Size?\n");
	scanf("%d", &removesize);
	if(counter==0){
		printf("There are no reservations\n");
		return;
	}
	for(i=0;i<SIZE;i++){
		if(removesize>=size[i]){//this determines whether a spot that opened up applies to any of  the people currently waiting
			flag=1;
			printf("Removing %s, party of %d\n", names[i], size[i]);
			names[i][0]='\0';//deleting the value currently in the array 
			size[i]=0;
			for(j=i;j<SIZE;j++){
				size[j]=size[j+1];	
				strcpy(names[j], names[j+1]);
			}//moving up all the values in the list up 1
			counter--;
			return;
			
		}
	}
		if(flag==0){
			printf("There are no reservations of the inputted size\n");
		}
	
	return;
}

void list(){
	int i;
	if(counter==0){
		printf("There are no reservations\n");
		return;
	}
	for(i=0;i<counter;i++){
		printf("Party of %d, under name %s.\n", size[i], names[i]);
	}//listing all the reservation list info
	return;
}
