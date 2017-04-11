#include "jeu.hpp"
#include "jeu_io.hpp"
#include "joueur_simple.hpp"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Prototypes
void choix_utilisateur(int choix);

//Lancement du jeu.
int main(int argc, char** argv){
	bool done = true;

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

	while(done == true){
		cout << "Selectionnez une option :" << endl;
		cout << "  - 1 : Ajouter un joueur simple" << endl;
		cout << "  - 2 : Ajouter un joueur organisée" << endl;
		cout << "  - 3 : Ajouter un joueur opportuniste" << endl;
		cout << "  - 4 : Ajouter un joueur humain" << endl;
		cout << "  - 5 : Lancer le jeu" << endl;
		cout << "  - 0 : Quitter le jeu" << endl;

		cout << endl;

		int choix;

		cout << "Votre choix : ";
		cin >> choix;

		choix_utilisateur(choix);

		done = false;

	}
	

	jeu_suppr(jeu) ;

	return EXIT_SUCCESS;
}


void choix_utilisateur(int choix){


}