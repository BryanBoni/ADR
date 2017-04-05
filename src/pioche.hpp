#ifndef ARAIL_PIOCHE_H
#define ARAIL_PIOCHE_H

#include <cstdlib>

//structure de données
struct DynamicTab{
	char* ptr;
	size_t size;//number of current element
	size_t capacity;//max number of elements that can contain the table
	size_t elementSize;//size taken in memory by one element.
};

struct Pioche {
	DynamicTab* deck;//pioche in french
  	DynamicTab* graveyard;//défausse in french
};

//initialisation de la pioche.
//  - taille_elt est le nombre d'octets necessaires pour stocker une carte
void pioche_init(Pioche& pioche, int taille_elt) ;

//pioche d'une carte
//  - cible est l'adresse d'une zone memoire ou la carte piochee est inscrite
void pioche_pioche(Pioche& pioche, void* cible) ;

//defausse d'une carte
//  - carte est l'adresse d'une zone memoire ou la carte defaussee est inscrite
void pioche_defausse(Pioche& pioche, const void* carte) ;

//melange de la pioche. Toutes les cartes (pioche et defausse) sont melangees
//pour former une nouvelle pioche.
void pioche_melange(Pioche& pioche) ;

//liberation de la memoire occupee par la pioche. Apres cette fonction il est
//necessaire d'appeler a nouveau init pour que la pioche puisse etre utilisee.
void pioche_suppr(Pioche& pioche) ;

#endif
