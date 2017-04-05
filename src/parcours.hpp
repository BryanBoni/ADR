#include <vector>



/*
villes est de la taille nb_villes -1, la villes[ville_depart] = 0, le reste vaut -1
dijkstra renvoi villes avec villes[v] = index du prédécésseur de v sur le plus cours chemin de ville_depart à v;
*/
void dijkstra(vector<Liaison>  liaisons, vector<int>& villes, int joueur);

