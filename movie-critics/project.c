#include <stdio.h>
#include "fileutil.c"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INITIALIZE_SIZE 100
#define STRING_LENGTH 150

typedef struct entry{
    
    char *word;
    int appearance;
    int sum_score;
    struct entry *next;
    
}entryT;


typedef struct hash{
    
    int size;
    int num_entries;
    entryT *table;
    
}hashT;

hashT *root;

unsigned long hash(char *str){
    
    unsigned long hash = 5381;
    int c;
    
    while (( c = *str++))
        hash = (((hash << 5) + hash) + c);
    
    return hash;
}

void insert_to_Hash(int hindex,char* word,int score){					//eisagwgi ston hash table
	
	entryT* current = root[hindex].table;
	int flag=0;						//gia elegxo an ulopoii9ike mia leitourgeia
	
	while(current!=NULL){						//an den einai adeios o hash table
		if(strcmp(current->word,word)==0){					//elegxei an uparxei to stoixeio
			current->appearance++;
			current->sum_score += score;
			flag++;
			break;
		}
		else{
			current = current->next;
		}
	}
	
	current = root[hindex].table;
	if(!flag){						//se periptwsi pou prepei na eisax9ei
		current = (entryT *)malloc(sizeof(entryT));
		if (current == NULL){
			printf("Error at malloc\n");
			exit(1);
		}

		if (root[hindex].table == NULL){				//periptwsi pou den uparxei lista
			
			current -> word = word;
			current -> sum_score = score;
			current -> next = NULL;
			current -> appearance = 1;
			root[hindex].table = current;
		
		}
		else {						//eisagwgi stin arxi tis listas
			
			current -> word = word;
			current -> sum_score = score;
			current -> appearance = 1;
			current -> next = root[hindex].table;
			root[hindex].table = current;
			
		}
	}
	root->num_entries++;
}

void position_insert(char *word,int score){				//briskei tin 9esi pou 9a eisax9ei sto hash table o kombos
	
	unsigned long key = hash(word);
	int hashIndex;
	hashIndex = key % root->size;
	
	insert_to_Hash(hashIndex,word,score);
	
}

void destroy_hash(){				//katastrefei ton hash table
	
	int i=0;
	entryT* current;
	entryT *temp;
	
	for (i=0; i<root -> size; i++){
		current = root[i].table;
		while(current != NULL){
			temp = current -> next;
			free(current);
			current = temp;
		}
	}
	root = NULL;
}

int rehash_position(char *word){			//briskei tin 9esi pou 9a eisax9ei o kombos meta to rehash
	
	unsigned long key = hash(word);
	int hashIndex;
	hashIndex = key % root -> size;
	
	return (hashIndex);
	
}

void rehash_insert(int position,entryT *current){			//sunartisi eisagwgis ston neo hash table
	
	
	if (root[position].table == NULL){
		
		current -> next = NULL;
		root[position].table = current;
		
	}
	else {
		
		current -> next = root[position].table;
		root[position].table = current;
		
	}
	
}

void rehash(){
	
	int i;
	hashT *temp=root;
	
	
	root = (hashT *)calloc(2*temp->size,sizeof(hashT));
	
	if (root == NULL){
		printf("Something went wrong with memory allocation!\n");
		exit(1);
	}
	
	root->size = 2*temp->size;
	root -> num_entries = temp -> num_entries;
	
	
	for (i=0; i<root->size; i++){
		root[i].table = NULL;
	}
	
	entryT *current;
	
	for (i=0; i<temp->size; i++){
		/*diatrexei ton proigoumeno hash table gia na dei an uparxoun stoixeia kai na ginei i anakatanomi*/
		current = temp[i].table;
		while (current != NULL){
			int position;
			position = rehash_position(current -> word);
			rehash_insert(position,current);
			current = current ->next;
			
		}
		
	}
	
}

void print(){
	
	entryT *current;
	
	int i=0;
	
	printf("\n");
	for (i=0; i<root->size; i++){
		current = root[i].table;
		if (current != NULL ){
			printf("%4d: ",i);
			while (current != NULL){
				if (current -> next == NULL){
					printf ("[ %c%s%c %d %.2lf ]\n",34,current -> word,34, current -> appearance,(double) current -> sum_score);
					current = current -> next;
				}
				else {
					printf ("[ %c%s%c %d %.2lf ], ",34,current -> word,34, current -> appearance,(double) current -> sum_score);
					current = current -> next;
				}
			}
		}
	}
	printf("\n");
}

entryT *best_word(entryT *head){
	
	double average_score;
	
	if (head == NULL){
		return NULL;
	}
	else {
		entryT *temp;
		
		average_score = head -> sum_score / head -> appearance;
		if (head -> next == NULL){ 
			return (head);
		}
		else {
			temp = best_word(head->next);
			return ((average_score > temp -> sum_score / temp -> appearance) ? head : temp);
		}
	}


}

entryT *absolute_word(entryT *array[],int pos){
	
	double average_score ;
	
	if (array[pos]!=NULL){
		average_score = array[pos] -> sum_score / array[pos] -> appearance;
		if (pos < root -> size){
			
			entryT *temp;
			temp = absolute_word(array,(pos+1));
			return ( average_score > (temp -> sum_score / temp -> appearance) ? array[pos] : temp);
			
		}
		else {
			return (array[pos]);
		}
	}
	else {
		return (absolute_word(array,(pos+1)));
	}
	
	
}




int main(int argc, char *argv[]){
    
		if (argc<2 || argc>3){
			printf("Incorect number of parameters\n");
		}
		else{
			int i, score, load_factor;
			char *line=NULL, *word;
			char delim[]={' ','\t'};
			
			root = (hashT *)calloc(100,sizeof(hashT));
			if (root == NULL){
				printf("Error at memory allocation\n");
			}
			else{
				for (i=0;i<INITIALIZE_SIZE; i++){			//arxikopoiisi
					root[i].size = 100;
					root[i].num_entries = 0;
					root[i].table = NULL;
				} 
			}
			
			line=read_next_line(argv[1]);					//pairnoume tin prwti protasi
			while (line!=NULL){
				score = atoi(line);
				line = line + 2;				//prospername to score kai to prwto keno
				word = strtok(line,delim);			//spame tin protasi se le3eis
				while (word!=NULL){
					for (i=0; i<strlen(word); i++){
						word[i] = tolower(word[i]);				//metatropi kefalaiwn se mikra
					}
					position_insert(word,score);
					load_factor = (root->num_entries/root->size);
					if (load_factor>3){						//sin9iki gia to rehash
						rehash();
					}
					word = strtok(NULL,delim);
				}
				line=read_next_line(argv[1]);
			}
			
			entryT *array[root->size], *the_best = NULL;
			int thesi=0;
			
			for (i=0; i < root -> size; i++){
				
				array[i] = best_word(root[i].table);			//briskoume tin kaluteri le3i apo ka9e keli toy hash table
				
			}
			
			
			the_best = absolute_word(array,thesi);				//briskoume tin pio kali apo tis kaluteres le3eis
			
			printf("The most positive word is %c%s%c with a score of %.3lf\n",34,the_best -> word,34,(double) (the_best -> sum_score / the_best -> appearance));
			
			if (strcmp(argv[2],"-p") == 0){
				print();
			}
			
			do{
				
				printf ("\n");
				printf("Enter review or DONE to finish:\n");
				
				char string[STRING_LENGTH];
				
				fgets(string,STRING_LENGTH,stdin);
				string[strlen(string)-1]='\0';
				
				if (strcmp(string,"DONE") == 0){
					break;
				}
				
				if (string[0]=='\0'){
					printf("Sorry, there is no score for this review!\n");
				}
				else{
					double review_score=0;
					
					word = strtok(string,delim);			//spame tin protasi
					entryT *curr;
					while (word != NULL){
						for (i=0; i<strlen(word); i++){
							word[i] = tolower(word[i]);			//metatropi kefalaiwn se mikra
						}
						for (i=0; i < root -> size; i++){
							curr = root[i].table;
							while (curr != NULL){
								if (strcmp(word, curr -> word) == 0){
									 review_score = review_score + (double)curr -> sum_score / curr -> appearance;
								}
								curr = curr -> next;
							}
						}
						
						word = strtok(NULL,delim);
					}
					printf("Review score: %1.4lf\n",review_score);
					if (review_score < 2){
						printf("This review is negative.\n");
					}
					else if(review_score > 2){
						printf("This review is positive.\n");
					}
					else{
						printf("This review is neutral.\n");
					}
					
				}
			
			}while(1);
			
			destroy_hash();

		}
    
        
    return 0;
}

