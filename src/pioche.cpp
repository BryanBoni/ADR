#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <math.h>//use .h because without it the compiler dont find it.
#include <cstring>
#include "pioche.hpp"

using namespace std;

/*
This class is used to initiate the draw system
*/
void pioche_init(Pioche& pioche, int taille_elt) {
	DynamicTab* deck = (DynamicTab*) malloc(sizeof(DynamicTab));
	deck->ptr = (char*) malloc(taille_elt*10);
	deck->size = 0;
	deck->elementSize = taille_elt;
	deck->capacity = 10;
	pioche.deck = deck;

	//cout << "pioche initialisé" << endl;

	DynamicTab* graveyard = (DynamicTab*) malloc(sizeof(DynamicTab));
	graveyard->ptr = (char*) malloc(taille_elt*10);
	graveyard->size = 0;
	graveyard->elementSize = taille_elt;
	graveyard->capacity = 10;
	pioche.graveyard = graveyard;

	//cout << "Cimetière initialisé" << endl;
}

void pioche_defausse(Pioche& pioche, const void* elt) {
	if(pioche.graveyard->capacity == pioche.graveyard->size){
		pioche.graveyard->capacity += 10;
		pioche.graveyard->ptr = (char*) realloc(pioche.graveyard->ptr, pioche.graveyard->elementSize * pioche.graveyard->capacity);
	}
    memcpy( pioche.graveyard->ptr + (pioche.graveyard->size * pioche.graveyard->elementSize), elt, pioche.graveyard->elementSize);
    pioche.graveyard->size += 1;
}

void pioche_pioche(Pioche& pioche, void* target) {
  //... votre code ici
    if(pioche.deck->size == 0)
        pioche_melange(pioche);
    memcpy(target, pioche.deck->ptr + (pioche.deck->size - 1) * pioche.deck->elementSize, pioche.deck->elementSize);
    pioche.deck->size -= 1;

}

void pioche_melange(Pioche& pioche) {
	while(pioche.deck->size > 0)
	{
		pioche_defausse(pioche, pioche.deck->ptr + pioche.deck->elementSize * (pioche.deck->size - 1));
		pioche.deck->size--;
	}
	void* tmp = malloc(pioche.deck->elementSize);
	srand(time(nullptr));
	for (int i = pioche.graveyard->size -1; i >=1; i--)
	{
		int pos = rand() % (i+1);
		memcpy(tmp, pioche.graveyard->ptr + (pioche.graveyard->elementSize * i),pioche.graveyard->elementSize);
		memcpy(pioche.graveyard->ptr + (pioche.graveyard->elementSize * i), pioche.graveyard->ptr + (pioche.graveyard->elementSize * pos), pioche.graveyard->elementSize);
		memcpy(pioche.graveyard->ptr + (pioche.graveyard->elementSize * pos), tmp, pioche.graveyard->elementSize);
	}
    
	int taille = pioche.graveyard->size;
    if(pioche.deck->capacity <= pioche.graveyard->size){
		pioche.deck->capacity = pioche.graveyard->size + 10;
		pioche.deck->ptr = (char*) realloc(pioche.deck->ptr, pioche.deck->elementSize * pioche.deck->capacity);
	}
	for(int i = 0; i < taille; i++)
	{
		memcpy(pioche.deck->ptr + (pioche.deck->elementSize * i), pioche.graveyard->ptr + (pioche.graveyard->elementSize * i), pioche.graveyard->elementSize);
		pioche.deck->size++;
	}
    pioche.graveyard->size = 0;
	free(tmp);
}

void pioche_suppr(Pioche& pioche) {
  //... votre code ici
	free(pioche.deck->ptr);
	free(pioche.graveyard->ptr);
	delete pioche.deck;
	delete pioche.graveyard;
}
