#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

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

}