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

typedef struct File File;
struct File
{
	Element *premier;
};

void display(File *file)
{
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = file->premier;

	printf("High scores :\n");
	while (actuel != NULL)
	{
		printf("%s\t", actuel->name);
		printf("%d\n", actuel->value);
		actuel = actuel->suivant;
	}

	printf("\n");
}


void add(File *file, char* name, int value)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	if (file == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}

	nouveau->name = name;
	nouveau->value = value;
	nouveau->suivant = file->premier;
	file->premier = nouveau;
}

void sortedAdd(File *file, char* name, int value)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	if (file == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}

	nouveau->name = name;
	nouveau->value = value;


	Element *actuel = file->premier;
	
	//La liste est vide
	if (actuel==NULL)
	{
		nouveau->suivant = NULL;
		file->premier = nouveau;
		return;
	}

	//Insertion ordonnée par score
	while (actuel != NULL)
	{
		if(actuel->value > nouveau->value) //Si l'actuel est supérieur
		{
			if(actuel->suivant==NULL || actuel->suivant->value <= nouveau->value) //ET que le suivant de l'actuel est inférieur ou inexistant
			{
				nouveau->suivant=actuel->suivant;
				actuel->suivant=nouveau;
				return;
			}
		}
		actuel = actuel->suivant;

		if (actuel==NULL)
		{
			//On arrive à la fin de la file, aucun score n'est plus élevé que "nouveau"
			//On place donc "nouveau" au début
			nouveau->suivant = file->premier;
			file->premier = nouveau;
			return;
		}
	}
}


Element* findByName(File *file, char* name)
{
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = file->premier;

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

void addOrUpdate(File *file, char* name, int value)
{
	Element* elementExistant;
	elementExistant=findByName(file,name);
	if (elementExistant!=NULL) {
		if(elementExistant->value < value)
		{
			elementExistant->value=value;
		}
	} else {
		add(file,name,value);
	}
}

// Retourne une nouvelle liste identique mais ordonnée par score
File* trier(File * file)
{
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}

	//nouvelle file qui sera triée
	File *fileTriee = malloc(sizeof(File));
	fileTriee->premier=NULL;

	Element *actuel = file->premier;
	while (actuel != NULL)
	{
		sortedAdd(fileTriee,actuel->name,actuel->value);
		actuel = actuel->suivant;
	}
	
	return fileTriee;
}


int main()
{
	File *maFile = malloc(sizeof(File));
	maFile->premier=NULL;

	//chargement du fichier et élimination des doublons
	addOrUpdate(maFile, "Toto",4);
	addOrUpdate(maFile,"Toto", 8);
	addOrUpdate(maFile, "Wiwi", 30);
	addOrUpdate(maFile, "Lulu", 15);
	addOrUpdate(maFile, "Lulu", 10);

	display(maFile);
	/*
	High scores :
	Lulu    15
	Wiwi    30
	Toto    8
	*/

	maFile=trier(maFile);
	display(maFile);
	/*
	High scores :
    Wiwi    30
    Lulu    15
    Toto    8
	*/

	return 0;
}
