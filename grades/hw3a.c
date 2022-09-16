#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define STUDENTS 100
#define COL 37
#define AEM 5
#define SIZE 11
#define GRADE 6

int main(int argc, char *argv[]) {
	char stoixeia[STUDENTS][COL];
	char input[COL],bathmos[GRADE];
	char *ptr, *komma, *teleia;
	int i=0, count, aem, grades[SIZE];
	double grade, sum=0, average;
	
	/*Sumplhrwsh tou pinaka stoixeia me bash ta stoixeia twn foithtwn kai ektupwsh twn zhtoumenwn stoixeiwn*/
	do{
		fgets(input,COL+1,stdin);
		ptr=input;
		if(atoi(ptr)<0){
			break;
		}
		else {
			strcpy(stoixeia[i],input);
			stoixeia[i][COL-1]='\0';
			i++;
			count++;
		}
		komma=strchr(ptr, ',');
		*(komma)='\0';
		teleia=strchr(komma+1,'.');
		*(ptr+AEM)='\0';
		aem=atoi(ptr);
		printf("%c. %s %d %.1lf\n", *(komma+1), ptr+AEM+1, aem, atof(teleia-2));
		
	}while (aem>=0 && i<STUDENTS);
	
	for(i=0; i<11; i++){
		grades[i]=0;
	}
	/*Sumplhrwsh tou pinaka grades me bash tous bathmous twn foithtwn*/
	for(i=0; i<count; i++){
		teleia=strchr(stoixeia[i],'.');
		teleia=teleia-2;
		strcpy(bathmos,teleia);
		grade=atof(bathmos);
		if(grade==0.0){
			grades[0]++;
		}
		else if(grade>0.0 && grade<=1.0){
			grades[1]++;
		}
		else if(grade>1.0 && grade<=2.0){
			grades[2]++;
		}
		else if(grade>2.0 && grade<=3.0){
			grades[3]++;
		}
		else if(grade>3.0 && grade<=4.0){
			grades[4]++;
		}
		else if(grade>4.0 && grade<=5.0){
			grades[5]++;
		}
		else if(grade>5.0 && grade<=6.0){
			grades[6]++;
		}
		else if(grade>6.0 && grade<=7.0){
			grades[7]++;
		}
		else if(grade>7.0 && grade<=8.0){
			grades[8]++;
		}
		else if(grade>8.0 && grade<=9.0){
			grades[9]++;
		}
		else if(grade>9.0 && grade<=10.0){
			grades[10]++;
		}
		sum=sum+grade;
	}
	
	/*ektupwsh istogrammatos*/
	printf("[ 0,  0]: ");
	for(i=0; i<grades[0]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[0]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 0,  1]: ");
	for(i=0; i<grades[1]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[1]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 1,  2]: ");
	for(i=0; i<grades[2]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[2]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 2,  3]: ");
	for(i=0; i<grades[3]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[3]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 3,  4]: ");
	for(i=0; i<grades[4]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[4]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 4,  5]: ");
	for(i=0; i<grades[5]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[5]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 5,  6]: ");
	for(i=0; i<grades[6]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[6]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 6,  7]: ");
	for(i=0; i<grades[7]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[7]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 7,  8]: ");
	for(i=0; i<grades[8]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[8]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 8,  9]: ");
	for(i=0; i<grades[9]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[9]%10; i++){
		printf("-");
	}
	printf("\n");
	
	printf("( 9, 10]: ");
	for(i=0; i<grades[10]/10; i++){
		printf("*");
	}
	for(i=0; i<grades[10]%10; i++){
		printf("-");
	}
	printf("\n\n");
	
	/*upologismos kai ektupwsh mesou orou*/
	average=sum/count;
	printf("AVERAGE: %.2lf\n", average);
	
	return 0;
}