//Lab 5 Sabiq Khan Tuesday 2:15
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
INFO *head=NULL;
INFO *tail=NULL;//Setting pointers of type INFO pointing to NULL
void insert(void);
void removeParty(void);
void list(void);
void search_size(void);
int check_duplicate(char[]);//GLOBAL VARIABLES

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
				return 0;
			default:
			printf("Bad option. Pick 1, 2, 3, or 0.\n");
		}
	}
}

void insert(){
	int checker;
	INFO *temp;
	char name[LENGTH];
	printf("Name?\n");
	scanf("%s", name);
	if(head!=NULL){//If the head isn't pointing to NULL, this will carry out
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
			tail->next=temp;//pointing the current tail->next to where our temp is
			tail=temp;//pointing tail to our temp
			tail->next=NULL;//pointing our new tail->next to NULL
				
	}
	}
	else{	//if the head does equal NULL, if the list is empty
		temp=(INFO*)malloc(sizeof(INFO));
		strcpy(temp->names, name);
		printf("Number of people?\n");
		scanf("%d",&temp->size);
		head=temp;//setting the head and tail pointing to the same point as temp
		tail=temp;
		temp->next=NULL;//temp->next is being set to point to NULL
	}
	return;
}

void removeParty(){
	int removesize, i,j;
	int flag=0;
	if(head==NULL){
		printf("There are no reservations\n");
		return;
	}
	printf("Size?\n");
	scanf("%d", &removesize);
	INFO *p=head;
	INFO *q=head;
	while(p!=NULL){//traversing through the linked list
		if(removesize>=p->size){
			if(p==head){
				if(tail==head){
					tail=NULL;
					}
				flag=1;
				printf("Removing %s, party of %d\n", p->names, p->size);
				head=head->next;//if the removesize applies to the head
				free(p);
				return;
			}
			if(p==tail){
				flag=1;
				printf("Removing %s, party of %d\n", p->names, p->size);
				tail=q;
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
		if(flag==0){
			printf("There are no reservations of the inputted size\n");
		}
	
	return;
}

void list(){
	if(head==NULL){
		printf("There are no reservations\n");
		return;
	}
	INFO *p=head;
	while(p!=NULL){
		printf("Party of %d, under name %s.\n", p->size, p->names);
		p=p->next;
	}//listing all the reservation info by going through the nodes, setting the pointer going through them equal to the subsequent address of the next node
	return;
}
void search_size(){//goes through the linked list, looking for a size from the nodes that are smaller than the size that was scanned in
	int searchsize;
	INFO *p=head;
	printf("Size?\n");
	scanf("%d", &searchsize);
	while(p!=NULL){
		if(searchsize>=p->size){
			printf("%s applies with a size of %d\n", p->names, p->size);
		}
		p=p->next;
	}
	return;
}

int check_duplicate(char temp[]){//checks duplicates from an inputted name from the insert function by going through the linked list and checking the nodes to see if any of the names match
	int temp2;
	INFO *p=head;
	while(p!=NULL){
		temp2=strcmp(temp, p->names);
		if(temp2==0){
			return 0;
		}
		p=p->next;
	}
	return 1;
}
