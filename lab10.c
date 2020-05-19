//Lab 10 Sabiq Khan Tuesday 2:15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
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
void insert(char[], int);
void removeParty(void);
void list(void);
void search_size(void);
int check_duplicate(char[]);
void clear_function(INFO*);
void read_file(char*, int);
void save_file(char*, int);
void listBack(INFO*);
void nameBack(char[]);
void * autoSave(void*);
void displaySave(char*);
pthread_mutex_t mutex;
//GLOBAL VARIABLES

int main(int argc, char *argv[]){
	int input, i, groupsize;
	char name[LENGTH];
	INFO *p;
	int key=atoi(argv[3]);
	read_file(argv[1], key);
	if(argc==1){
		printf("the file name is missing\n");
		return 0;
	}
	pthread_t thread_id;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_id, NULL, autoSave, (void*)argv[2]);
	while(1){
		printf("Press 1 to add to the waiting list\n");
		printf("Press 2 to remove someone from the list\n");
		printf("Press 3 to show who is currently waiting\n");
		printf("Press 4 to show who is currently waiting with a party smaller than an inputted size\n");
		printf("Press 5 to show the list backwards\n");
		printf("Press 6 to show the names backwards\n");
		printf("Press 7 to display the autosave\n");
		printf("Press 0 to quit\n");
		scanf("%d", &input);

		switch(input){
			case 1:
				printf("Name?\n");
				scanf("%s", name);
				printf("Group size?\n");
				scanf("%d", &groupsize);
				insert(name, groupsize);
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
			case 5://feeding each linked list's head into the list backwards function
				for(i=0;i<4;i++){
					listBack(x[i].head);
				}
				break;
			case 6://feeding each name into the backwards name function
				for(i=0;i<4;i++){
					p=x[i].head;
					while(p!=NULL){
						nameBack(p->names);
						printf("\n");
						p=p->next;
					}
				}
				break;
			case 7:
				displaySave(argv[2]);
				break;
			case 0://feeding each linked list's head into the clear memory function
			pthread_mutex_lock(&mutex);
				save_file(argv[1], key);
				for(i=0;i<4;i++){
					clear_function(x[i].head);
				}
			pthread_mutex_unlock(&mutex);
				printf("Memory cleared\nFile Saved\n");
				return 0;
			default:
			printf("Bad option. Pick 1, 2, 3, 4, 5, or 0.\n");
		}
	}
}

void * autoSave(void *file){//autosaving the nodes into a binary file every 15 seconds
	INFO *p;
	FILE *fp;
	int i;
	while(1){
		pthread_mutex_lock(&mutex);
		fp=fopen(file, "wb");
		if(fp==NULL){
			printf("error\n");
			pthread_mutex_unlock(&mutex);
			return NULL;
		}
		for(i=0;i<4;i++){
			p=x[i].head;
			while(p!=NULL){
				fwrite(p, sizeof(INFO), 1, fp);
				p=p->next;
			}
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex);
		printf("Autosaved\n");
		sleep(15);
		}
	return NULL;
}

void displaySave(char *file){//getting the data from the binary file and printing it
	FILE *fp;
	fp=fopen(file, "rb");
	INFO temp;
	printf("Name    Size\n");
	pthread_mutex_lock(&mutex);
	while(fread(&temp, sizeof(INFO), 1, fp)==1){
		printf("%s     %d\n", temp.names, temp.size);
	}
	pthread_mutex_unlock(&mutex);
return;
}

void listBack(INFO *temp){//printing the list in backwards order recursively
	if(temp==NULL){
		return;
	}
	listBack(temp->next);
	printf("%d under the name %s\n", temp->size, temp->names);
	return;
}

void nameBack(char temp[LENGTH]){//listing all the names backwards recursively
	char *p=temp;
	if(*p=='\0'){
		return;
	}
	nameBack(p+1);
	printf("%c",*p);
	return;
}

void read_file(char* file, int key){//opening a text file and putting the values into linked lists
	int groupsize;
	int i;
	char name[LENGTH];
	char temp[70];
	char*p;
	FILE *fp=fopen(file, "r");
	if(fp==NULL){
		printf("Error opening file\n");
		return;
	}
	while(fgets(temp, 70, fp)!=NULL){
		p=temp;
		while(*p!='\n'){
			*p=((*p^key));
			p++;
		}
		sscanf(temp, "%s\t%d\n", name, &groupsize);
		insert(name, groupsize);
	}
	fclose(fp);
	return;
}

void save_file(char*file, int key){//saving the memory from the linked lists into a text file
	int i, j;
	char *q;
	FILE *fp=fopen(file, "w");
	INFO *p;
	char buffer[70];
	fprintf(fp,"Name\tGroup Size\n_______________\n");
	for(i=0;i<4;i++){
		p=x[i].head;
		while(p!=NULL){
			sprintf(buffer,"%s\t%d\n", p->names, p->size);
			q=buffer;
			while(*q!='\n'){
				*q=((*q^key));
				q++;
			}
			fprintf(fp,"%s", buffer);
			p=p->next;
		}
	}
	fclose(fp);
	return;
}


void insert(char name[LENGTH], int groupsize){
	int checker, number;
	INFO *temp;
	checker=check_duplicate(name);//Going through the checker function. It only needs to go through the checker function if the list isn't empty.
	if(checker==0){
		printf("There is already a reservation under that name\n");
		return;
		}
	else{
		temp=(INFO*)malloc(sizeof(INFO));//giving a pointer of type info that points to a chunk of memory that was allocated of the size of struct INFO, and setting that equal to our INFO pointer temp
			strcpy(temp->names, name);
			temp->size=groupsize;
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
				pthread_mutex_lock(&mutex);
				x[number].tail->next=temp;
				x[number].tail=temp;
				x[number].tail->next=NULL;
				pthread_mutex_unlock(&mutex);
				return;
			}
			if(x[number].head==NULL){
				pthread_mutex_lock(&mutex);
				x[number].head=temp;//setting the head and tail pointing to the same point as temp
				x[number].tail=temp;
				temp->next=NULL;//temp->next is being set to point to NULL
				pthread_mutex_unlock(&mutex);
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
			pthread_mutex_lock(&mutex);
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
			pthread_mutex_unlock(&mutex);
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
void clear_function(INFO *temp){//clearing the memory recursively
	if(temp==NULL){
		return;
	}
	clear_function(temp->next);
	free(temp);
	return;
}


