#include <iostream>
#include <cstdio>
#include <cstdlib>

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
	deck->ptr = malloc(taille_elt*10);
	deck->size = 0;
	deck->elementSize = taille_elt;
	deck->capacity = 10;
	pioche.graveyard = graveyard;

	//cout << "Cimetière initialisé" << endl;
}

void pioche_defausse(Pioche& pioche, const void* elt) {
	
}

void pioche_pioche(Pioche& pioche, void* target) {
  //... votre code ici
}

void pioche_melange(Pioche& pioche) {
  //... votre code ici
}

void pioche_suppr(Pioche& pioche) {
  //... votre code ici
}
