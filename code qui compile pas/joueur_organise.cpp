#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

#include "joueur_organise.hpp"
#include "parcours.cpp"

using namespace std;

//initialisation
void joueur_organise_init(JoueurOrganise& joueur) {
	joueur.cartes_couleur = vector<Carte>();
	joueur.cartes_objectif = vector<Objectif>();
	joueur.score = 0;
	joueur.mdp = joueur_organise_mdp(joueur);
}

/*
pas utilie pour le joueur simple pour l'instant 
car la libération de la mémoire se fait automatiquement.
*/
void joueur_organise_suppr(JoueurOrganise& joueur) {
	//RIEN NON RIEN DE RIEN JE NE REGRETTE RIEN, NI LA.....
	//rien à faire ici.
}

/*
Créé un mot de passe pour le joueur.
*/
int joueur_organise_mdp(JoueurOrganise& joueur) {
	srand(time(nullptr));
	return rand() % (4000);
}

/*
Assigne un id au joueur
*/
void joueur_organise_config_indice(JoueurOrganise& joueur, int indice) {
	joueur.id = indice;
}

/*
Le joueur fait soit :
	- la pioche de l'objectif et calcul du plus court chemin
	- la pioche de 2 cartes wagon (face recto si celle voulu, sinon pioche face verso)
	- Achete une liason avec une carte wagon
	-
*/
void joueur_organise_tour(Jeu& jeu, JoueurOrganise& joueur) {
	if(joueur.cartes_objectif.size() < 1){
		joueur.cartes_objectif.push_back(jeu_pioche_objectif(jeu, joueur.id, joueur.mdp));
		cout << "le joueur " << joueur.id << " tire une carte objectif : \n - ville 1 : " << joueur.cartes_objectif[0].ville1 << "\n - ville 2 : " << joueur.cartes_objectif[0].ville2 << "\n - gains possibles : "<< joueur.cartes_objectif[0].points << "\n" <<endl;
	
	}else{
		bool canPlay = false;
		vector<Liaison> chemin;
		vector<Carte>::iterator toPay;
		Liaison toBuy;
		vector<int> carte_a_prendre;
		int dist = 0;

		if((dist = chemin_a_prendre(chemin, jeu, joueur.id, joueur.cartes_objectif.back().ville1, joueur.cartes_objectif.back().ville2)) >=0){
			cout << "chemin taille : " <<chemin.size() << "\n";
			if(chemin.size() == 0){ // Il n'y a aucune carte à acheter, mais le chemin est possible --> l'objectif est réalisé
			
				joueur.objectifs_complete.push_back(joueur.cartes_objectif.back());
				joueur.cartes_objectif.pop_back();				
			}
			else{
				for(Liaison l : chemin)
					cout << l.ville1 << " a " << l.ville2 << "\n";
				cout << "cartes en main : \n";
				for( Carte c : joueur.cartes_couleur)
					cout << c.couleur << "\n";

				
				vector<int> priority = vector<int>();
				for(unsigned int i = 0; i < chemin.size(); i++)
				{
					vector<Liaison> liaisons_partielle = jeu.liaisons;
					for(vector<Liaison>::iterator it = liaisons_partielle.begin(); it != liaisons_partielle.end(); ++it)
					{
						if(it->ville1 == chemin[i].ville1 && it->ville2 == chemin[i].ville2 && it->longueur == chemin[i].longueur)
						{
							liaisons_partielle.erase(it);
							it = liaisons_partielle.end();
						}
					}
					priority.push_back(distance_chemin_a_prendre(jeu_nb_villes(jeu), liaisons_partielle, joueur.id, joueur.cartes_objectif.back().ville1, joueur.cartes_objectif.back().ville2) - dist);	
				}

				unsigned int max_priority_pos = 0;
				for(unsigned int i = 0; i < priority.size(); i++)
				{
					if(priority[i] > priority[max_priority_pos])
						max_priority_pos = i;
				}

				if(joueur.cartes_couleur.size() > 0){
					for(unsigned int i = 0; i < chemin.size(); i++){
						for(vector<Carte>::iterator it = joueur.cartes_couleur.begin(); it != joueur.cartes_couleur.end(); ++it){		
							if(chemin[i].couleur == it->couleur && (chemin[i].couleur != chemin[max_priority_pos].couleur || i == max_priority_pos) && (canPlay && (toBuy.ville1 != chemin[max_priority_pos].ville1 && toBuy.ville2 != chemin[max_priority_pos].ville2))){
								canPlay = true;
								toBuy = chemin[i];
								toPay = it;
							}
						}
					}
				}
				if(canPlay == true){
					jeu_prendre_liaison(jeu, toBuy.ville1, toBuy.ville2, joueur.id, joueur.mdp);
					jeu_defausse(jeu, *toPay, joueur.id, joueur.mdp);
					joueur.cartes_couleur.erase(toPay);
					cout << "Le joueur " << joueur.id << " à pris la liason :" << toBuy.ville1 << " " << toBuy.ville2 << " pour la couleur" << toBuy.couleur << endl;

				}else{
					int carte_pioche = 0;
					vector<Liaison> tmp = vector<Liaison>();
					tmp.push_back(chemin[max_priority_pos]);
					cartes_necessaire_visible(jeu, tmp, carte_a_prendre);
					for(int i : carte_a_prendre){
						joueur.cartes_couleur.push_back(jeu_pioche_visible(jeu, i, joueur.id, joueur.mdp));
						carte_pioche++;
					}

					for(vector<Liaison>::iterator it = chemin.begin(); it != chemin.end(); ++it)
					{
						if(it->ville1 == chemin[max_priority_pos].ville1 && it->ville2 == chemin[max_priority_pos].ville2 && it->longueur == chemin[max_priority_pos].longueur)
						{
							chemin.erase(it);
							it = chemin.end();
						}
					}

					cartes_necessaire_visible(jeu, chemin, carte_a_prendre);
					
					for(int i : carte_a_prendre){
						if(carte_pioche < 2){
							joueur.cartes_couleur.push_back(jeu_pioche_visible(jeu, i, joueur.id, joueur.mdp));
							carte_pioche++;
						}
					}

					cout << "Le Joueur " << joueur.id << " pioche "<< carte_pioche <<" cartes visibles" <<endl;
					for(int i = 0; i + carte_pioche < 2; i++)
						joueur.cartes_couleur.push_back(jeu_pioche_cache(jeu, joueur.id, joueur.mdp));
					cout << "Le Joueur " << joueur.id << " pioche "<< 2-carte_pioche <<" cartes face caché" <<endl;
				}
			}
		}
		else{
			cout << "objectif impossible à remplir\n";
			joueur.cartes_objectif.push_back(jeu_pioche_objectif(jeu, joueur.id, joueur.mdp));
			cout << "le joueur " << joueur.id << " tire une carte objectif : \n - ville 1 : " << joueur.cartes_objectif.back().ville1 << "\n - ville 2 : " << joueur.cartes_objectif.back().ville2 << "\n - gains possibles : "<< joueur.cartes_objectif.back().points << "\n" <<endl;
		}
	} 

}
