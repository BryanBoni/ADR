#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>

#include "joueur_simple.hpp"

using namespace std;

void joueur_simple_init(JoueurSimple& joueur) {
	joueur.cartes_couleur = vector<Carte>();
	joueur.cartes_objectif = vector<Objectif>();
	joueur.score = 0;
	joueur.mdp = joueur_simple_mdp(joueur);
}

void joueur_simple_suppr(JoueurSimple& joueur) {
	//RIEN NON RIEN DE RIEN JE NE REGRETTE RIEN, NI LA.....
}

int joueur_simple_mdp(JoueurSimple& joueur) {
	srand(time(nullptr));
	return rand() % (4000);
}

void joueur_simple_config_indice(JoueurSimple& joueur, int indice) {
	joueur.id = indice;
}

void joueur_simple_tour(Jeu& jeu, JoueurSimple& joueur) {
//todo 
}
