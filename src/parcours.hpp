#pragma once

#include <vector>



/*
Villes est de la taille nb_villes -1, la villes[ville_depart] = 0, 
le reste vaut -1.
Dijkstra renvoi le vecteur villes avec villes[v] = index du prédécésseur de v 
sur le plus cours chemin de ville_depart à v;
*/
void dijkstra(vector<Liaison>  liaisons, vector<int>& villes, int joueur);


/*
Renvoi dans chemin la suite de liaison que doit prendre le joueur appelant, 
Cette suite representant le chemin le plus court possible à prendre.

Cette fonction appel la fonction dijkstra qui lui renvoi une suite de ville qu'elle
utilisera pour choisir les liaisons qui irons dans chemin.
*/
void chemin_a_prendre(vector<Liaison> chemin, Jeu& jeu, int joueur);

/*
retourne vrai si les cartes visibles sont necessaire au joueur
à la complétion d'une liaison objectifs, et les ajoutes au vecteur carte_a_prendre.
faux si non.
*/
bool cartes_necessaire_visible(Jeu& jeu, vector<Liaison> chemin, vector<int> carte_a_prendre);