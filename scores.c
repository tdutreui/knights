/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element Element;
struct Element
{
	int value;
	char* name;
	Element *suivant;
};

typedef struct Pile Pile;
struct Pile
{
	Element *premier;
};

void afficherPile(Pile *pile)
{
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = pile->premier;

    printf("High scores :\n");
	while (actuel != NULL)
	{
		printf("%s\t", actuel->name);
		printf("%d\n", actuel->value);
		actuel = actuel->suivant;
	}

	printf("\n");
}

void empiler(Pile *pile, char* name, int value)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	if (pile == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}

	nouveau->name = name;
	nouveau->value = value;
	nouveau->suivant = pile->premier;
	pile->premier = nouveau;
}


Element* findByName(Pile *pile, char* name)
{
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = pile->premier;

	while (actuel != NULL)
	{
		if(strcmp(actuel->name,name)==0)
		{
			return actuel;
		}
		actuel = actuel->suivant;
	}

	return NULL;
}


void addOrUpdate(Pile *pile, char* name, int value)
{
	Element* elementExistant;
	elementExistant=findByName(pile,name);
	if (elementExistant!=NULL) {
		if(elementExistant->value < value)
		{
			elementExistant->value=value;
		}
	} else {
		empiler(pile,name,value);
	}
}


int main()
{
	Pile *maPile = malloc(sizeof(Pile));

	addOrUpdate(maPile, "Toto",4);
	addOrUpdate(maPile,"Toto", 8);
	addOrUpdate(maPile, "Lulu", 15);
	addOrUpdate(maPile, "Lulu", 10);

	afficherPile(maPile);
	/*
	High scores :
    Lulu    15
    Toto    8
	*/

	return 0;
}
