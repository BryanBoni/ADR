#ifndef ARAIL_JOUEUR_SIMPLE_HPP
#define ARAIL_JOUEUR_SIMPLE_HPP

#include <vector>

#include "jeu.hpp"

using namespace std;
struct JoueurSimple {
	int id;
	vector<Carte> cartes_couleur;
	vector<Objectif> cartes_objectif;
	vector<Objectif> objectifs_complete;
	int score;
	int mdp;
};

//initialisation
void joueur_simple_init(JoueurSimple& joueur);

//suppression
void joueur_simple_suppr(JoueurSimple& joueur);

//acces au mot de passe a fournir au jeu. Le mot de passe sert a s'assurer que
//le joueur ne tente pas de se faire passer pour un autre. Il sera utilise par
//le joueur pour toutes les actions sur le jeu qui verifient l'identite du
//joueur.
int joueur_simple_mdp(JoueurSimple& joueur);

//prise en compte de l'indice du joueur fourni par le jeu. Le joueur pourra
//utiliser cet indice pour s'identifier aupres du jeu pour les actions qui le
//demandent : piocher, defausser, prendre des liaisons, ...
void joueur_simple_config_indice(JoueurSimple& joueur, int indice);

//un tour de jeu pour le joueur simple
void joueur_simple_tour(Jeu& jeu, JoueurSimple& joueur);


//Joueur Organise
struct JoueurOrganise {
	int id;
	vector<Carte> cartes_couleur;
	vector<Objectif> cartes_objectif;
	vector<Objectif> objectifs_complete;
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



//Joueur Organise
struct JoueurOpportuniste {
	int id;
	vector<Carte> cartes_couleur;
	vector<Objectif> cartes_objectif;
	vector<Objectif> objectifs_complete;
	int score;
	int mdp;
};

//initialisation
void joueur_opportuniste_init(JoueurOrganise& joueur);

//suppression
void joueur_opportuniste_suppr(JoueurOrganise& joueur);

//acces au mot de passe a fournir au jeu. Le mot de passe sert a s'assurer que
//le joueur ne tente pas de se faire passer pour un autre. Il sera utilise par
//le joueur pour toutes les actions sur le jeu qui verifient l'identite du
//joueur.
int joueur_opportuniste_mdp(JoueurOrganise& joueur);

//prise en compte de l'indice du joueur fourni par le jeu. Le joueur pourra
//utiliser cet indice pour s'identifier aupres du jeu pour les actions qui le
//demandent : piocher, defausser, prendre des liaisons, ...
void joueur_opportuniste_config_indice(JoueurOrganise& joueur, int indice);

//un tour de jeu pour le joueur simple
void joueur_opportuniste_tour(Jeu& jeu, JoueurOrganise& joueur);


//Joueur utilisateur


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

#endif
