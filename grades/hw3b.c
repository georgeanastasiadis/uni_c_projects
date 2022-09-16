#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 26
#define MAX_STUDENTS 100
#define COL 37
#define AEM 5

typedef struct studentData {
	int aem;
	char onoma[MAX_LEN];
	double grade;
}dataT;

/*sunarthsh pou diavazei ta soixeia twn foithtwn kai epistrefei twn arithmo twn foithtwn*/ 
int epistrofi(dataT *info){
	char *ptr, *komma, *teleia, *name;
	char input[COL];
	int i=0, count;
	
	do{
		fgets(input,COL+1,stdin);
		ptr=input;
		if(atoi(ptr)<0){
			break;
		}
		else {
			input[COL-1]='\0';
			i++;
			count++;
		}
		komma=strchr(ptr, ',');
		teleia=strchr(komma+1,'.');
		*(ptr+AEM)='\0';
		name=strchr(ptr+AEM+1,' ');
		*name='\0';
		name=ptr+AEM+1;
		info[i-1].aem=atoi(ptr);
		info[i-1].grade=atof(teleia-2);
		strcpy(info[i-1].onoma,name);
		strcpy(input,"");
	}while (atoi(ptr)>=0 && i<MAX_STUDENTS);
	
	
	
	return (count);
}

/*sunarthsh pou ektupwnei ta apaitoumena stoixeia gia kathe foithth*/
void printer(dataT info[MAX_STUDENTS],int count){
	
	int i;
	char *ptr;
	
	for (i=0; i<count; i++){
		ptr=strchr(info[i].onoma,',');
		*ptr='\0';
		printf("%c. ",*(ptr+1));
		ptr=info[i].onoma;
		printf("%s %d %.1lf\n",ptr,info[i].aem,info[i].grade);
	}
	
}

void ektipwsi(){
	int i;
	printf("\n");
	for (i=0; i<20; i++){
		printf("-");
	}
	printf("\n");
}

/*taxinomhsh pinaka me bash to onomatepwnumo kate foithth*/
void selection_sort(dataT *info,int plithos){
	int i, wall, min, temp_aem;
	double temp_grade;
	char *temp;
	for (wall=0; wall<plithos; wall++){
		min=wall;
		for (i=wall+1; i<plithos; i++){
			if ( strcmp(info[i].onoma,info[min].onoma)<0){
				min=i;
			}
			else if(strcmp(info[i].onoma,info[min].onoma)==0){
				if (info[i].aem<info[min].aem){
					min=i;
				}
			}
		}
		if (min != wall){
			temp=info[wall].onoma;
			strcpy(info[wall].onoma,info[min].onoma);
			strcpy(info[min].onoma,temp);
			temp_aem = info[wall].aem;
			info[wall].aem = info[min].aem;
			info[min].aem = temp_aem;
			temp_grade = info[wall].grade;
			info[wall].grade = info[min].grade;
			info[min].grade = temp_grade;
			
		}
	}
}

void insertion_sort(dataT *info,int plithos){
	int wall, pos,aemtosort;
	char *nametosort;
	
	for (wall=1; wall<plithos; wall++){
		nametosort=info[wall].onoma;
		aemtosort=info[wall].aem;
		pos = wall - 1;
		
		while (pos>=0 && strcmp(info[pos].onoma,nametosort)>0){
			
			strcpy(info[wall+1].onoma,info[pos].onoma);
			info[wall+1].aem = info[pos].aem;
			info[wall+1].grade = info[pos].grade;
			pos--;
		}
		
		if (strcmp(info[pos].onoma,nametosort)==0){
			while (pos>=0 && info[pos].aem > aemtosort){
				info[wall+1].aem = info[pos].aem;
				info[wall+1].grade = info[pos].grade;
			}
			
			info[pos+1].aem = aemtosort;
		}
		
		strcpy(info[pos+1].onoma,nametosort);
	}
}

int main (int argc, char* argv[]){
	int i, count;
	dataT info[MAX_STUDENTS];
	
	for (i=0; i<MAX_STUDENTS; i++){
		info[i].aem=-1;
	}
	
	for (i=0; i<MAX_STUDENTS; i++){
		strcpy(info[i].onoma," ");
	}
	
	for (i=0; i<MAX_STUDENTS; i++){
		info[i].grade=-2;
	}
	
	count=epistrofi(info);
	//printer(info,count);
	
	ektipwsi();
	//selection_sort(info,count);
	//printer(info,count);
	
	insertion_sort(info,count);
	printer(info,count);
	
	ektipwsi();
	
	return 0;
}



