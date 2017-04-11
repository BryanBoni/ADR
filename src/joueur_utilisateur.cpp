#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include "joueur_utilisateur.hpp"
#include "parcours.cpp"

using namespace std;

//initialisation
void joueur_utilisateur_init(JoueurUtilisateur& joueur) {
	joueur.cartes_couleur = vector<Carte>();
	joueur.cartes_objectif = vector<Objectif>();
	joueur.objectifs_complete = vector<Objectif>();
	joueur.score = 0;
	joueur.mdp = joueur_utilisateur_mdp(joueur);
}

/*
pas utilie pour le joueur Utilisateur pour l'instant 
car la libération de la mémoire se fait automatiquement.
*/
void joueur_utilisateur_suppr(JoueurUtilisateur& joueur) {
	//RIEN NON RIEN DE RIEN JE NE REGRETTE RIEN
	//rien à faire ici.
}

/*
L'utilisateur créé un mot de passe pour le joueur.
*/
int joueur_utilisateur_mdp(JoueurUtilisateur& joueur) {
	cout << "Veuillez choisir un mot de passe (un entier) : ";
	
	cin >> joueur.mdp;

	cout << "\n Mot de passe assigné avec succès !\n" << endl;
	return joueur.mdp;
}

/*
Assigne un id au joueur
*/
void joueur_utilisateur_config_indice(JoueurUtilisateur& joueur, int indice) {
	joueur.id = indice;
}

/*
L'utilisateur peut soit :
	- Piocher une catre objectif
	- Piocher deux carte liaison (visible ou face caché) 
	- Achete une liason avec une carte wagon
*/
void joueur_utilisateur_tour(Jeu& jeu, JoueurUtilisateur& joueur) {
	//jeu_affiche_historique(jeu);
	int action;
	bool done = false;

	cout << "# Nouveau tour pour le joueur "<< joueur.id <<" #" << endl;

	//affichage des informations du joueur
	cout << "Cartes couleur disponible";
	for(int i = 0; i<5; i++){
		cout << "Id carte: " << i << " couleur :" << jeu_nom_couleur(jeu, jeu.cartes_visibles[i].couleur) << ", ";
	}
	cour << "\n" << endl;

	cout << "Votre main :\n - Objectif(s) : ";
	for(Objectif o : joueur.cartes_objectif)
		cout << "Ville1 : "  << o.ville1 << " vers Ville2 : " << o.ville2 << ", ";

	cout << "\n - Couleur(s) :";
	for(Carte c : joueur.cartes_couleur)
		cout << jeu_nom_couleur(jeu, c.couleur) << ", ";

	cout << "\n Score actuel : " << joueur.score << endl;

	while(done == false){
		cout << "Veuillez choisir une action : \n  1. Tirer une carte Objectif\n  2. Tirer deux cartes couleur\n  3. Prendre une liaison" << endl;
		cin >> action;

		switch(action){
			case 1:{
				joueur.cartes_objectif.push_back(jeu_pioche_objectif(jeu, joueur.id, joueur.mdp));
				cout << "Vous tirez une carte objectif : \n - ville 1 : " << joueur.cartes_objectif[0].ville1 << "\n - ville 2 : " << joueur.cartes_objectif[0].ville2 << "\n - gains possibles : "<< joueur.cartes_objectif[0].points << "\n" <<endl;
				done = true;
				break;
			}case 2:{
				char c;
				cout << "Piocher une carte visible ? (y/n)" << endl;
				cin >> c;
				if(c == 'y'){
					int e1 = -1, e2;
					bool done2 = false;

					while(done2 == false){
						if(e1 >= 0 && e1 < 5 && e1 != e2){
							cout << "Choix 2: ";
							cin << e2; 
							done2 = true;
						}else if(e1 < 0 && e1 >= 5){
							cout << "Choix 1 : ";
							cin << e1; 
						}else{
							cout << "carte inconue, choisiser en une autre"<< endl;
						}
					}

					joueur.cartes_couleur.push_back(jeu_pioche_visible(jeu, e1, joueur.id, joueur.mdp));
					joueur.cartes_couleur.push_back(jeu_pioche_visible(jeu, e2, joueur.id, joueur.mdp));
					cout << "cartes piochée !" << endl;
					done = true;
					break;
				}else{
					joueur.cartes_couleur.push_back(jeu_pioche_cache(jeu, joueur.id, joueur.mdp));
					joueur.cartes_couleur.push_back(jeu_pioche_cache(jeu, joueur.id, joueur.mdp));
					cout << "cartes piochée ! \n votre main : " << endl;
					for(Carte c : joueur.cartes_couleur)
						cout << "Id carte: " << i << " couleur :" << jeu_nom_couleur(jeu, c.couleur) << ", ";
					cout << endl;
					done = true;
					break;
				}
			}case 3:{
				bool done2 = false;
				int v1 = -1, v2;

				cout << "Veuillez choisir une liaison, sinon entrez 1337 pour retourner au menu précédent" << endl;
				while(done2 == false){
					cout << "Ville 1: ";
					cin >> v1;

					if(v1 == 1337){
						done2 = true;
					}else{
						cout << "Ville 2: ";
						cin >> v2;
						if(v2 == 1337){
							done2 = true;
						}else{
							int c;
							cout << "Couleur ? ";
							cin >> c;
							jeu_prendre_liaison(jeu, v1, v2, joueur.id, joueur.mdp);
							jeu_defausse(jeu, *joueur.cartes_couleur[c], joueur.id, joueur.mdp);
							joueur.cartes_couleur.erase(joueur.cartes_couleur[c]);
							cout << "Vous avez pris la liason :" << v1 << " " << v2 << " pour la couleur" << jeu_nom_couleur(jeu, c) << endl;

							done2 = true;
							done = true;
						}
					}
				}
				break;
			}default :{
				cout << "Commande invalide Veuillez réessayer\n" << endl;
				break;
			}
		}
	}
}
