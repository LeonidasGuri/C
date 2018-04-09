#include <stdio.h>
#include <stdlib.h>

void read_delete_file(void);
void read_visits_file(void);

struct node{
	char id[26];
	float kostos;
};

struct node table[4]; 

int compare(const void *a_, const void *b_)
{
   struct node *a = (struct node*)a_;
   struct node *b = (struct node*)b_;
   if ( a->kostos > b->kostos)
      return 1;

   else if (a->kostos < b->kostos)
      return -1;

   else
      return 0;
}

int main(){

	int choice;

	while(1)
	{
		printf("1. Read deletions file\n");
		printf("2. Read visits file\n");
		printf("3. Quit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				read_delete_file();
				break;
			case 2:
				read_visits_file();
				break;
			case 3:
				exit (0);
				break;
			default:
				printf("Wrong choice\n");
				break;
		}
	}
  	system("PAUSE");	
	return 0;
}

void read_delete_file(void){
	printf("Read file\n");
}
void read_visits_file(void){

	char kwdikos[26];
	int etos;
	int hmera;
	float poso;
	FILE *fp1;
	char *pch;
	char line[200];
	int counter,i;
		
	fp1=fopen("a.txt","r");
	counter=0;
	while(fgets(line,100,fp1)!=NULL && feof( fp1 ) == 0 ){
		printf("line=%s\n",line);
		pch = strtok (line,";");
		strcpy(table[counter].id,pch);
		printf("Kwdikos:%s\n",pch);
		pch = strtok (NULL, ";");
		etos=atoi(pch);
		printf("etos:%d\n",etos);
		pch = strtok (NULL, ";");
		hmera=atoi(pch);	
		printf("hmera:%d\n",hmera);
		pch = strtok (NULL, ";");
		poso = atof (pch);
		table[counter].kostos=poso;
		printf("poso=%f\n",poso);
		counter++;
	}
	for(i=0;i<4;i++)
	{
		printf("Id:%s kostos:%f\n",table[i].id,table[i].kostos);
	}
	qsort(table,4,sizeof(struct node),compare);
	for(i=0;i<4;i++)
        {
                printf("Id:%s kostos:%f\n",table[i].id,table[i].kostos);
        }
}

