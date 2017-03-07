#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>//use .h because without it the compiler dont find it.

#include "pioche.hpp"

using namespace std;

/*
This class is used to initiate the draw system
*/
void pioche_init(Pioche& pioche, int taille_elt) {
	DynamicTab *deck = new DynamicTab;
	deck->ptr = malloc(taille_elt*10);
	deck->size = 0;
	deck->elementSize = taille_elt;
	deck->capacity = 10;
	pioche.deck = deck;

	//cout << "pioche initialisé" << endl;

	DynamicTab *graveyard = new DynamicTab;
	graveyard->ptr = malloc(taille_elt*10);
	graveyard->size = 0;
	graveyard->elementSize = taille_elt;
	graveyard->capacity = 10;
	pioche.graveyard = graveyard;

	//cout << "Cimetière initialisé" << endl;
}

void pioche_defausse(Pioche& pioche, const void* elt) {
	if(pioche.graveyard->capacity == pioche.graveyard->size){
		pioche.graveyard->capacity += 10;
		pioche.graveyard->ptr = realloc(pioche.graveyard->ptr, 
			(pioche.graveyard->elementSize*pioche.graveyard->capacity)+10);
	}
	//void* locationCopy = (char*);
	//pioche.graveyard->ptr[1] = elt;
}

void pioche_pioche(Pioche& pioche, void* target) {
  //... votre code ici
}

void pioche_melange(Pioche& pioche) {
  //Pseudo code
	int i = 0;
	void* temp;
	//change pioche with graveyard ?

	//Shuffle
	int n = pioche.deck->size;
	while(n >= 0){
		i = floor(random() * n--);
		temp = pioche.deck->ptr[n];
		pioche.deck->ptr[n] = pioche.deck->ptr[n];
		pioche.deck->ptr[n] = temp; 
	}
}

void pioche_suppr(Pioche& pioche) {
  //Pseudo code
}
