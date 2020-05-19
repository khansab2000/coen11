//Lab 6 Sabiq Khan Tuesday 2:15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define LENGTH 20 
typedef struct info{
	char names[LENGTH];
	int size;
	struct info *next;
}INFO;
typedef struct list{
	INFO *head;
	INFO *tail;
}LIST;
LIST x[4]={{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}};	//Setting pointers of type INFO pointing to NULL
void insert(void);
void removeParty(void);
void list(void);
void search_size(void);
int check_duplicate(char[]);
void clear_function(void);
//GLOBAL VARIABLES

int main(void){
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
				clear_function();
				return 0;
			default:
			printf("Bad option. Pick 1, 2, 3, 4, 5, or 0.\n");
		}
	}
}

void insert(){
	int checker, number;
	INFO *temp;
	char name[LENGTH];
	printf("Name?\n");
	scanf("%s", name);
	checker=check_duplicate(name);//Going through the checker function. It only needs to go through the checker function if the list isn't empty.
	if(checker==0){
		printf("There is already a reservation under that name\n");
		return;
		}
	else{
		temp=(INFO*)malloc(sizeof(INFO));//giving a pointer of type info that points to a chunk of memory that was allocated of the size of struct INFO, and setting that equal to our INFO pointer temp
			strcpy(temp->names, name);
			printf("Number of people?\n");
			scanf("%d",&temp->size);
			if(temp->size==1||temp->size==2){
				number=0;
			}		
			if(temp->size==3||temp->size==4){
				number=1;
			}
			if(temp->size==5||temp->size==6){
				number=2;
			}
			if(temp->size>6){
				number=3;
			}
			if(x[number].head!=NULL){
				x[number].tail->next=temp;
				x[number].tail=temp;
				x[number].tail->next=NULL;
				return;
			}
			if(x[number].head==NULL){
				x[number].head=temp;//setting the head and tail pointing to the same point as temp
				x[number].tail=temp;
				temp->next=NULL;//temp->next is being set to point to NULL
				return;
			}
	}
	return;
}

void removeParty(){
	int removesize, i,j;
	int flag=0;
	int counter=0;
	for(i=0;i<4;i++){
		if(x[i].head==NULL){
		counter++;
		}
	}
	if(counter==4){
		printf("There are no reservations\n");
	}
	printf("Size?\n");
	scanf("%d", &removesize);
	for(i=0;i<4;i++){
		INFO *p=x[i].head;
		INFO *q=x[i].head;
		while(p!=NULL){//traversing through the linked list
			if(removesize>=p->size){
				if(p==x[i].head){
					if(x[i].tail==x[i].head){
						x[i].tail=NULL;
						}
					flag=1;
					printf("Removing %s, party of %d\n", p->names, p->size);
					x[i].head=x[i].head->next;//if the removesize applies to the head
					free(p);
					return;
				}
				if(p==x[i].tail){
					flag=1;
					printf("Removing %s, party of %d\n", p->names, p->size);
					x[i].tail=q;
					q->next=NULL;
					free(p);
					return;//if the remove size applies to the tail
				}
				flag=1;
				printf("Removing %s, party of %d\n", p->names, p->size); 
				q->next=p->next;
				free(p);
				return;
				}
			q=p;//making sure q is one node behind p so we can point q->next to p->next in order to delete. 
			p=p->next;
		}
	}
	if(flag==0){
		printf("There are no reservations of the inputted size\n");
	}
	return;
}

void list(){
	int i;
	int flag=0;
	for(i=0;i<4;i++){
		if(x[i].head==NULL){
			flag++;
		}
		INFO *p=x[i].head;
		while(p!=NULL){
			printf("Party of %d, under name %s.\n", p->size, p->names);
			p=p->next;
		}//listing all the reservation info by going through the nodes, setting the pointer going through them equal to the subsequent address of the next node
		if(flag==4){
			printf("There are no reservations\n");
		}
	}
		return;
}
void search_size(){//goes through the linked list, looking for a size from the nodes that are smaller than the size that was scanned in
	int searchsize;
	int i;
	int size=0;
	printf("Size?\n");
	scanf("%d", &searchsize);
	if(searchsize<3){
		size=1;
	}
	if(searchsize==3||searchsize==4){
		size=2;
	}
	if(searchsize==5||searchsize==6){
		size=3;
	}
	if(searchsize>6){
		size=4;
	}
	for(i=0;i<size;i++){
		INFO *p=x[i].head;
		while(p!=NULL){
			if(searchsize>=p->size){
				printf("%s applies with a size of %d\n", p->names, p->size);
			}
			p=p->next;
		}
}
return;
}

int check_duplicate(char temp[]){//checks duplicates from an inputted name from the insert function by going through the linked list and checking the nodes to see if any of the names match
	int temp2, i;
	for(i=0;i<4;i++){
		INFO *p=x[i].head;
		while(p!=NULL){
			temp2=strcmp(temp, p->names);
			if(temp2==0){
				return 0;
			}
			p=p->next;
		}
	}
	return 1;
}
void clear_function(){//traversing the linked list with two pointers, clearing the memory as it goes through
	int i;
	INFO *p;
	INFO *q;
	for(i=0;i<4;i++){
		p=x[i].head;
		q=x[i].head;
		while(p!=NULL){
			q=p;
			p=p->next;
			free(q);
		}
	}
	printf("Memory Cleared\n");
	return;
}


