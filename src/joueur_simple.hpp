#ifndef ARAIL_JOUEUR_SIMPLE_HPP
#define ARAIL_JOUEUR_SIMPLE_HPP

#include <vector>

#include "jeu.hpp"

using namespace std;
struct JoueurSimple {
	int id;
	vector<Carte> cartes_couleur;
	vector<Objectif> cartes_objectif;
	int score;
	int mdp;
};

//initialisation
void joueur_simple_init(JoueurSimple& joueur) ;

//suppression
void joueur_simple_suppr(JoueurSimple& joueur) ;

//acces au mot de passe a fournir au jeu. Le mot de passe sert a s'assurer que
//le joueur ne tente pas de se faire passer pour un autre. Il sera utilise par
//le joueur pour toutes les actions sur le jeu qui verifient l'identite du
//joueur.
int joueur_simple_mdp(JoueurSimple& joueur) ;

//prise en compte de l'indice du joueur fourni par le jeu. Le joueur pourra
//utiliser cet indice pour s'identifier aupres du jeu pour les actions qui le
//demandent : piocher, defausser, prendre des liaisons, ...
void joueur_simple_config_indice(JoueurSimple& joueur, int indice) ;

//un tour de jeu pour le joueur simple
void joueur_simple_tour(Jeu& jeu, JoueurSimple& joueur) ;

#endif