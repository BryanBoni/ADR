#include "jeu.hpp"
#include "jeu_io.hpp"
#include "joueur_simple.hpp"
//#include "joueur_organise.hpp"
#include "joueur_container.cpp"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Prototypes
int choix_utilisateur(int choix, int index, Jeu& jeu, vector<JoueurContainer>& liste_des_joueurs);
void play_game(Jeu& jeu, vector<JoueurContainer>& liste_des_joueurs);

//Lancement du jeu.
int main(int argc, char** argv){
	vector<JoueurContainer> liste_des_joueurs;
	bool done = true;
	int index = 0;



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

		index = choix_utilisateur(choix, index, jeu, liste_des_joueurs);

		cout << liste_des_joueurs.size() << endl;
	}
	
	return EXIT_SUCCESS;
}

/*Choix d'un élément de la composition des joueurs du jeu*/
int choix_utilisateur(int choix, int index, Jeu& jeu, vector<JoueurContainer>& liste_des_joueurs){
	cout << "\n" << endl;

	switch(choix){
		case 0 :{
			jeu_suppr(jeu);
			exit(EXIT_SUCCESS);
			break;			
		}
		case 1 :{
			//joueur simple
			JoueurSimple joueur;
			joueur_simple_init(joueur) ;

			//ajout du joueur à la partie
			index = jeu_ajout_joueur(jeu, joueur_simple_mdp(joueur));
			joueur_simple_config_indice(joueur, index) ;

			JoueurContainer jc; 
			jc.type = 1;
			jc.js = joueur;

			liste_des_joueurs.push_back(jc);

			cout << "Joueur Simple ajouté !" << endl;
			break;
		}
		case 2 :{
			
			//joueur organisée
			JoueurOrganise joueurO;
			joueur_organise_init(joueurO) ;

			//ajout du joueur à la partie
			index = jeu_ajout_joueur(jeu, joueur_organise_mdp(joueurO));
			joueur_organise_config_indice(joueurO, index) ;

			JoueurContainer jc; 
			jc.type = 2;
			jc.jo = joueurO;

			liste_des_joueurs.push_back(jc);

			cout << "Joueur organisée ajouté !" << endl;
			
			break;
		}
		case 3 :{
			//Ici Joueur Opportuniste
			/*
			JoueurContainer jc; 
			jc.type = 3;
			jc.js = joueurOp;

			liste_des_joueurs.push_back(jc);
			*/
			cout << "Joueur en chantier !" << endl;
			break;
		}
		case 4 :{
			//Ici Joueur Controlleur
			JoueurUtilisateur joueurU;
			joueur_utilisateur_init(joueurU) ;

			//ajout du joueur à la partie
			index = jeu_ajout_joueur(jeu, joueur_utilisateur_mdp(joueurU));
			joueur_utilisateur_config_indice(joueurU, index) ;
			
			JoueurContainer jc; 
			jc.type = 4;
			jc.ju = joueurU;

			liste_des_joueurs.push_back(jc);

			cout << "Joueur utilisateur ajouté !" << endl;
			
			break;
		}
		case 5 :{
			if(index > 1){
				cout << "Lancement de la partie, nombre de joueurs " << index << endl;
				//cout << liste_des_joueurs[0].type << endl;
				//cout << "bite" << endl;
				play_game(jeu, liste_des_joueurs);
			}else{
				cout << "Nombre de joueurs insuffisant (2 minimum) " << endl;
			}
			break;
		}
		default:{
			cout << "Commande inconnue, veuillez réessayer !" << endl;
			break;			
		}
	}

	cout << "\n" << endl;
	return index;
}

void play_game(Jeu& jeu, vector<JoueurContainer>& liste_des_joueurs){
	//cout << "bite" << endl;
	for(int i = 0; i < 30; i++){
		//cout << "bite2" << endl;
		for(JoueurContainer jc: liste_des_joueurs){
			//cout << "bite3" << endl;
			cout << jc.type << endl;
			switch(jc.type){
				case 1:{
					joueur_simple_tour(jeu, jc.js);
					break;
				}
				case 2:{
					//Joueur Organiser
					joueur_organise_tour(jeu, jc.jo);
					break;
				}
				case 3:{
					//Joueur Opportuniste
					break;
				}
				case 4:{
					//Joueur utilisateur
					joueur_utilisateur_tour(jeu, jc.ju);
					break;
				}
				default:{
					cout << "Zut ça marche pas" << endl;
					break;
				}
			}
		}
	}

	//historique
	jeu_affiche_historique(jeu) ;
	
	int a = 0;

	for(JoueurContainer jct : liste_des_joueurs){
		int score = 0;
		switch(jct.type){
			case 1:{
				for(Objectif o : liste_des_joueurs[a].js.objectifs_complete)
					score += o.points;
				score -= liste_des_joueurs[a].js.cartes_objectif.size() * 10;
				cout << "score joueur " << jct.js.id << " : " << score <<endl;
			}
			case 2:{
				for(Objectif o : liste_des_joueurs[a].jo.objectifs_complete)
					score += o.points;
				score -= liste_des_joueurs[a].jo.cartes_objectif.size() * 10;
				cout << "score joueur " << jct.jo.id << " : " << score <<endl;
			}
			case 3:{
					//Joueur Opportuniste
			}
			case 4:{
				for(Objectif o : liste_des_joueurs[a].ju.objectifs_complete)
					score += o.points;
				score -= liste_des_joueurs[a].ju.cartes_objectif.size() * 10;
				cout << "score joueur " << jct.ju.id << " : " << score <<endl;
			}
		}
		a++;

	}


	//menage
	jeu_suppr(jeu) ;
	exit(EXIT_SUCCESS);
}
