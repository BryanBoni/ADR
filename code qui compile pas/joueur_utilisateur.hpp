#pragma once

#include <vector>

#include "jeu.hpp"

using namespace std;
struct JoueurUtilisateur {
	int id;
	vector<Carte> cartes_couleur;
	vector<Objectif> cartes_objectif;
	vector<Objectif> objectifs_complete;
	int score;
	int mdp;
};

//initialisation
void joueur_utilisateur_init(JoueurUtilisateur& joueur);

//suppression
void joueur_utilisateur_suppr(JoueurUtilisateur& joueur);

//acces au mot de passe a fournir au jeu, ici le joueur definira son mot de passe.
int joueur_utilisateur_mdp(JoueurUtilisateur& joueur);

//prise en compte de l'indice du joueur fourni par le jeu.
void joueur_utilisateur_config_indice(JoueurUtilisateur& joueur, int indice);

//un tour de jeu pour le joueur utilisateur
void joueur_utilisateur_tour(Jeu& jeu, JoueurUtilisateur& joueur);