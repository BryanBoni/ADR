#ifndef ARAIL_JOUEUR_ORGANISER_HPP
#define ARAIL_JOUEUR_ORGANISER_HPP

#include <vector>

#include "jeu.hpp"

using namespace std;
struct JoueurOrganise {
	int id;
	vector<Carte> cartes_couleur;
	vector<Objectif> cartes_objectif;
	int score;
	int mdp;
};

//initialisation
void joueur_organise_init(JoueurOrganise& joueur);

//suppression
void joueur_organise_suppr(JoueurOrganise& joueur);

//acces au mot de passe a fournir au jeu. Le mot de passe sert a s'assurer que
//le joueur ne tente pas de se faire passer pour un autre. Il sera utilise par
//le joueur pour toutes les actions sur le jeu qui verifient l'identite du
//joueur.
int joueur_organise_mdp(JoueurOrganise& joueur);

//prise en compte de l'indice du joueur fourni par le jeu. Le joueur pourra
//utiliser cet indice pour s'identifier aupres du jeu pour les actions qui le
//demandent : piocher, defausser, prendre des liaisons, ...
void joueur_organise_config_indice(JoueurOrganise& joueur, int indice);

//un tour de jeu pour le joueur simple
void joueur_organise_tour(Jeu& jeu, JoueurOrganise& joueur);

#endif