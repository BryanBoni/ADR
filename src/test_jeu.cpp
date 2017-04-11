#include "jeu.hpp"
#include "jeu_io.hpp"
#include "joueur_simple.hpp"



#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	
	//verification qu'un fichier est fourni
	if(argc < 2) {
		cout << "usage : " << argv[0] << " <config file>" << endl ;
		return 1 ;
	}

	//chargement du fichier
	ifstream file(argv[1]) ;

	//initialisation
	Jeu jeu ;
	jeu_init(jeu) ;

	//lecture de la configuration
	jeu_import(jeu, file) ;

	//finalisation
	jeu_debut_partie(jeu) ;
	
	//joueur simple
	JoueurOrganise joueur;
	joueur_organise_init(joueur) ;

	
	//ajout du joueur à la partie
	int index = jeu_ajout_joueur(jeu, joueur_organise_mdp(joueur)) ;
	joueur_organise_config_indice(joueur, index) ;


	//jeu
	for(int i = 0; i < 10; ++i) {
		joueur_organise_tour(jeu, joueur) ;
	}

	//historique
	jeu_affiche_historique(jeu) ;

	int score = 0;
	for(Objectif o : joueur.objectifs_complete)
		score += o.points;
	score -= joueur.cartes_objectif.size() * 10;
	cout << "score joueur 1 :" << score << "\n";
	//menage
	joueur_organise_suppr(joueur) ;

	jeu_suppr(jeu) ;

	return 0 ;
}
