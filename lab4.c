//Lab 4 Sabiq Khan Tuesday 2:15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define LENGTH 20 
typedef union extrainfo{
	char birthday[LENGTH];//name of birthday person
	int years;//years of anniversary
	float avg;//the average age of the party
}EXTRA;

typedef struct info{
	char names[LENGTH];
	int size;
	int special;
	EXTRA infoextra;
}INFO;

INFO entries[SIZE];
int counter;
void insert(void);
void removeParty(void);
void list(void);
void search_size(void);
int check_duplicate(char[]);//GLOBAL VARIABLES

int main(void){
	counter=0;
	int input, i;
	while(1){
		printf("Press 1 to add to the waiting list\n");
		printf("Press 2 to remove someone from the list\n");
		printf("Press 3 to show who is currently waiting\n");
		printf("Press 4 to show who is currently waiting with a party smaller than an inputted size\n");
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
			case 4:
				search_size();
				break;
			case 0:
				return 0;
			default:
				printf("Bad option. Pick 1, 2, 3, or 0.\n");
		}
	}
}

void insert(){
	char temp[LENGTH];
	int checker;
	INFO *p=&entries[counter];
	if(counter==SIZE){
		printf("The waiting list is full\n");
	}
	else{
		printf("Name?\n");
		scanf("%s", temp);
		checker=check_duplicate(temp);
		if(checker==0){
			printf("There is already a reservation under that name\n");
			return;
		}
		else{
			strcpy(entries[counter].names, temp);
		printf("Number of people?\n");
		scanf("%d",&entries[counter].size);
		printf("Special Occasion? Input 1 for a birthday, 2 for an anniversary, or any other number if there's no special occasion\n");
		scanf("%d", &p->special);
		switch(p->special){
			case 1:
				printf("What is the birthday person's name?\n");
				scanf("%s", p->infoextra.birthday);
				break;
			case 2:
				printf("How many years is the anniversary?\n");
				scanf("%d", &p->infoextra.years);
				break;
			default:
				printf("What is the average age of the party?\n");
				scanf("%f", &p->infoextra.avg);
				break;
		}//depending on what value was stored into the special variable, the switch statement will ask different questions and save the values into the union

		counter++;	//scanning in the inputted numbers into the arrays
	}
	return;
	}
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
	INFO *p=entries;
	for(i=0;i<counter;i++){
		if(removesize>=p->size){//this determines whether a spot that opened up applies to any of  the people currently waiting
			flag=1;
			printf("Removing %s, party of %d\n", p->names, p->size); 
			p->size=0;
			for(j=i;j<SIZE;j++){
				p->size=(p+1)->size;	
				strcpy(p->names, (p+1)->names);
				p->special=(p+1)->special;
				p->infoextra=(p+1)->infoextra;
				p++;
			}//moving up all the values in the list up 1
			counter--;
			return;
			
		}
		p++;
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
	INFO *p=entries;
	for(i=0;i<counter;i++){
		printf("Party of %d, under name %s.\n", p->size, p->names);
		switch(p->special){
			case 1:
				printf("With a birthday boy/girl whose name is %s\n", p->infoextra.birthday);
				break;
			case 2:
				printf("With an anniversary of %d years\n", p->infoextra.years);
				break;
			default:
				printf("With an average age of %f\n", p->infoextra.avg);
				break;//like before, depending on the special variable, the function will print out different things
		}
		p++;
	}//listing all the reservation list info
	return;
}
void search_size(){
	int i, searchsize;
	INFO *p=entries;
	printf("Size?\n");
	scanf("%d", &searchsize);
	for(i=0;i<counter;i++){
		if(searchsize>=p->size){
			printf("%s applies with a size of %d\n", p->names, p->size);
				switch(p->special){
					case 1:
						printf("With a birthday boy/girl whose name is %s\n", p->infoextra.birthday);
						break;
					case 2:
						printf("With an anniversary of %d years\n", p->infoextra.years);
						break;
					default:
						printf("With an average age of %f\n", p->infoextra.avg);
						break;
				}
		}
		p++;
	}
}

int check_duplicate(char temp[]){
	int i, temp2;
	INFO *p=entries;
	for(i=0;i<counter;i++){
		temp2=strcmp(temp, p->names);
		if(temp2==0){
			return 0;
		}
		p++;
	}
	return 1;
}
