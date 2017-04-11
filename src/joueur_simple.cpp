#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

#include "joueur_simple.hpp"
#include "parcours.cpp"

using namespace std;

//initialisation
void joueur_simple_init(JoueurSimple& joueur) {
	joueur.cartes_couleur = vector<Carte>();
	joueur.cartes_objectif = vector<Objectif>();
	joueur.objectifs_complete = vector<Objectif>();
	joueur.score = 0;
	joueur.mdp = joueur_simple_mdp(joueur);
}

/*
pas utilie pour le joueur simple pour l'instant 
car la libération de la mémoire se fait automatiquement.
*/
void joueur_simple_suppr(JoueurSimple& joueur) {
	//RIEN NON RIEN DE RIEN JE NE REGRETTE RIEN, NI LA.....
	//rien à faire ici.
}

/*
Créé un mot de passe pour le joueur.
*/
int joueur_simple_mdp(JoueurSimple& joueur) {
	srand(time(nullptr));
	return rand() % (4000);
}

/*
Assigne un id au joueur
*/
void joueur_simple_config_indice(JoueurSimple& joueur, int indice) {
	joueur.id = indice;
}

/*
Le joueur fait soit :
	- la pioche de l'objectif et calcul du plus court chemin
	- la pioche de 2 cartes wagon (face recto si celle voulu, sinon pioche face verso)
	- Achete une liason avec une carte wagon
*/
void joueur_simple_tour(Jeu& jeu, JoueurSimple& joueur) {
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

				if(joueur.cartes_couleur.size() > 0){
					for(Liaison l : chemin){
						for(vector<Carte>::iterator it = joueur.cartes_couleur.begin(); it != joueur.cartes_couleur.end(); ++it){		
							if(l.couleur == it->couleur){
								canPlay = true;
								toBuy = l;
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
					cartes_necessaire_visible(jeu, chemin, carte_a_prendre);
					int carte_pioche = 0;
					for(int i : carte_a_prendre){
						joueur.cartes_couleur.push_back(jeu_pioche_visible(jeu, i, joueur.id, joueur.mdp));
						carte_pioche++;
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







//Joueur Organise

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
					vector<Liaison>::iterator to_erase;
					vector<Liaison> liaisons_partielle = jeu.liaisons;
					for(vector<Liaison>::iterator it = liaisons_partielle.begin(); it != liaisons_partielle.end(); it++)
					{
						if(it->ville1 == chemin[i].ville1 && it->ville2 == chemin[i].ville2 && it->longueur == chemin[i].longueur)
						{
							to_erase = it;
						}
					}
					liaisons_partielle.erase(to_erase);
					priority.push_back(distance_chemin_a_prendre(jeu_nb_villes(jeu), liaisons_partielle, joueur.id, joueur.cartes_objectif.back().ville1, joueur.cartes_objectif.back().ville2) - dist);	

				}

				unsigned int max_priority_pos = 0;
				for(unsigned int i = 0; i < priority.size(); i++)
				{
					if(priority[i] > priority[max_priority_pos])
						max_priority_pos = i;
				}
				cout << "liaison prioritaire : " << chemin[max_priority_pos].ville1 << " a " << chemin[max_priority_pos].ville2 << " rajoute " << priority[max_priority_pos] << "\n";


				if(joueur.cartes_couleur.size() > 0){
					for(unsigned int i = 0; i < chemin.size(); i++){
						for(vector<Carte>::iterator it = joueur.cartes_couleur.begin(); it != joueur.cartes_couleur.end(); ++it){		
							if(chemin[i].couleur == it->couleur && (chemin[i].couleur != chemin[max_priority_pos].couleur || i == max_priority_pos) && ((toBuy.ville1 != chemin[max_priority_pos].ville1 && toBuy.ville2 != chemin[max_priority_pos].ville2))){
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
					vector<Liaison>::iterator to_erase;
					for(vector<Liaison>::iterator it = chemin.begin(); it != chemin.end(); ++it)
					{
						if(it->ville1 == chemin[max_priority_pos].ville1 && it->ville2 == chemin[max_priority_pos].ville2 && it->longueur == chemin[max_priority_pos].longueur)
						{
							to_erase = it;
						}
					}
					chemin.erase(to_erase);

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




/*
//Joueur Opportuniste

//initialisation
void joueur_opportuniste_init(JoueurOpportuniste& joueur) {
	joueur.cartes_couleur = vector<Carte>();
	joueur.cartes_objectif = vector<Objectif>();
	joueur.score = 0;
	joueur.mdp = joueur_opportuniste_mdp(joueur);
}

/*
pas utilie pour le joueur simple pour l'instant 
car la libération de la mémoire se fait automatiquement.
*/
/*void joueur_opportuniste_suppr(JoueurOpportuniste& joueur) {
	//RIEN NON RIEN DE RIEN JE NE REGRETTE RIEN, NI LA.....
	//rien à faire ici.
}

/*
Créé un mot de passe pour le joueur.
*//*
int joueur_opportuniste_mdp(JoueurOpportuniste& joueur) {
	srand(time(nullptr));
	return rand() % (4000);
}

/*
Assigne un id au joueur
*//*
void joueur_opportuniste_config_indice(JoueurOpportuniste& joueur, int indice) {
	joueur.id = indice;
}

/*
Le joueur fait soit :
	- la pioche de l'objectif et calcul du plus court chemin
	- la pioche de 2 cartes wagon (face recto si celle voulu, sinon pioche face verso)
	- Achete une liason avec une carte wagon
	-
*//*
void joueur_opportuniste_tour(Jeu& jeu, JoueurOpportuniste& joueur) {
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
					vector<Liaison>::iterator to_erase;
					vector<Liaison> liaisons_partielle = jeu.liaisons;
					for(vector<Liaison>::iterator it = liaisons_partielle.begin(); it != liaisons_partielle.end(); it++)
					{
						if(it->ville1 == chemin[i].ville1 && it->ville2 == chemin[i].ville2 && it->longueur == chemin[i].longueur)
						{
							to_erase = it;
						}
					}
					liaisons_partielle.erase(to_erase);
					priority.push_back(distance_chemin_a_prendre(jeu_nb_villes(jeu), liaisons_partielle, joueur.id, joueur.cartes_objectif.back().ville1, joueur.cartes_objectif.back().ville2) - dist);	

				}

				unsigned int max_priority_pos = 0;
				for(unsigned int i = 0; i < priority.size(); i++)
				{
					if(priority[i] > priority[max_priority_pos])
						max_priority_pos = i;
				}
				cout << "liaison prioritaire : " << chemin[max_priority_pos].ville1 << " a " << chemin[max_priority_pos].ville2 << " rajoute " << priority[max_priority_pos] << "\n";


				if(joueur.cartes_couleur.size() > 0){
					for(unsigned int i = 0; i < chemin.size(); i++){
						for(vector<Carte>::iterator it = joueur.cartes_couleur.begin(); it != joueur.cartes_couleur.end(); ++it){		
							if(chemin[i].couleur == it->couleur && (chemin[i].couleur != chemin[max_priority_pos].couleur || i == max_priority_pos) && ((toBuy.ville1 != chemin[max_priority_pos].ville1 && toBuy.ville2 != chemin[max_priority_pos].ville2))){
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
					vector<Liaison>::iterator to_erase;
					for(vector<Liaison>::iterator it = chemin.begin(); it != chemin.end(); ++it)
					{
						if(it->ville1 == chemin[max_priority_pos].ville1 && it->ville2 == chemin[max_priority_pos].ville2 && it->longueur == chemin[max_priority_pos].longueur)
						{
							to_erase = it;
						}
					}
					chemin.erase(to_erase);

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
*/





//Joueur utilisateur


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
	cout << "\n" << endl;

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
							cin >> e2; 
							done2 = true;
						}else if(e1 < 0 && e1 >= 5){
							cout << "Choix 1 : ";
							cin >> e1; 
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
					for(unsigned int i = 0; i < joueur.cartes_couleur.size(); i++)
						cout << "Id carte: " << i << " couleur :" << jeu_nom_couleur(jeu, joueur.cartes_couleur[i].couleur) << ", ";
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
							jeu_defausse(jeu, joueur.cartes_couleur[c], joueur.id, joueur.mdp);
							joueur.cartes_couleur.erase(joueur.cartes_couleur.begin() + c);
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

