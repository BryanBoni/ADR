#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

#include "joueur_simple.hpp"
#include "parcours.cpp"

using namespace std;

//initialisation
void joueur_simple_init(JoueurSimple& joueur) {
	joueur.cartes_couleur = vector<Carte>();
	joueur.cartes_objectif = vector<Objectif>();
	joueur.score = 0;
	joueur.mdp = joueur_simple_mdp(joueur);
}

/*
pas utilie pour le joueur simple pour l'instant 
car la libération de la mémoire se fait automatiquement.
*/
void joueur_simple_suppr(JoueurSimple& joueur) {
	//RIEN NON RIEN DE RIEN JE NE REGRETTE RIEN, NI LA.....
	//rien à faire ici.
}

/*
Créé un mot de passe pour le joueur.
*/
int joueur_simple_mdp(JoueurSimple& joueur) {
	srand(time(nullptr));
	return rand() % (4000);
}

/*
Assigne un id au joueur
*/
void joueur_simple_config_indice(JoueurSimple& joueur, int indice) {
	joueur.id = indice;
}

/*
Le joueur fait soit :
	- la pioche de l'objectif et calcul du plus court chemin
	- la pioche de 2 cartes wagon (face recto si celle voulu, sinon pioche face verso)
	- Achete une liason avec une carte wagon
*/
void joueur_simple_tour(Jeu& jeu, JoueurSimple& joueur) {
	//todo 
	bool can_play = true;

	vector<Liaison> chemin;
	vector<int> carte_a_prendre;

	chemin_a_prendre(chemin, jeu, joueur.id);

	if(joueur.cartes_objectif.size() < 1){
		joueur.cartes_objectif.push_back(jeu_pioche_objectif(jeu, joueur.id, joueur.mdp));
		cout << "le joueur " << joueur.id << " tire une carte."<<endl;
	}else if(can_play == true){

	}else{
		if(cartes_necessaire_visible(jeu, chemin, carte_a_prendre) == true){
			joueur.cartes_couleur.push_back(jeu_pioche_visible(jeu, carte_a_prendre[0], joueur.id, joueur.mdp));
			joueur.cartes_couleur.push_back(jeu_pioche_visible(jeu, carte_a_prendre[1], joueur.id, joueur.mdp));

		}
		joueur.cartes_couleur.push_back(jeu_pioche_cache(jeu, joueur.id, joueur.mdp));
	}
}

