#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct proionta{
	char product[4];
	struct proionta* next;
};


struct proionta* p = NULL;
struct proionta* pointer = NULL;
struct proionta* current = NULL;

int main(){

	int i;
	char proion[4];

	printf("Dwse proion\n");
        scanf("%s",proion);
	p = (struct proionta*)malloc(sizeof(struct proionta));
	strcpy(p->product,proion);
	p->next = NULL;
	current = p;
	for(i=0;i<3;i++){
		printf("Dwse proion\n");
		scanf("%s",proion);
		pointer = (struct proionta*)malloc(sizeof(struct proionta));
		strcpy(pointer->product,proion);
        	pointer->next = NULL;
		current->next = pointer;
		current = current->next;	
	}

	current = p;
	while(current!=NULL)
	{
		printf("%s\n",current->product);
		current=current->next;
	}

	system("PAUSE");	
    return 0;
}
