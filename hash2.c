#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct list_node {
    char kwdikos[100];
    float cost;
};

static struct list_node hashtab[HASHSIZE]; //declare the hash table


//function for hashing

unsigned hash(char *s) {

    unsigned hashval;

    for (hashval=0;*s!='\0';s++){
        hashval = *s + 31*hashval;
		printf("%d\n",*s);
    }  

    return hashval % HASHSIZE;

}

int main(){
	char buffer[100];
	int number[10];
	int position;
	float kostos;

	printf( "Dwse kwdiko\n" );
	scanf( "%s" , buffer);
	printf( "Dwse kostos\n" );
	scanf( "%f", &kostos );
	
	position = hash(buffer);
	//printf(" %d\n ", position);
	//printf("Buffer : %s\n",buffer);

	strcpy(hashtab[position].kwdikos, buffer);
	hashtab[position].cost = kostos;

	printf( "Kwdikos: %s, kostos: %f\n",hashtab[position].kwdikos, hashtab[position].cost);
	
  	system("PAUSE");
	return EXIT_SUCCESS;
}
