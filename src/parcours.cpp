#include "parcours.hpp"
#include "heap.cpp"
#include <cstdio>

using namespace std;


void dijkstra(vector<Liaison>&  liaisons, vector<int>& villes, int joueur)
{
    Heap hp;
    vector<int> dist = villes;
    vector<bool> mark;
    for(unsigned int i = 0; i < villes.size(); i++)
    {
        mark.push_back(false);
    }
    unsigned int i = 0;
    while(i < villes.size() && villes[i] != 0)
    {
        i++;
    }
    if(i < villes.size())
    {
        heap_push(hp, i, dist[i]);
    }


    while(heap_size(hp) > 0)
    {
        valuation vmin = heap_min(hp);
        heap_pop(hp);
        if(vmin.value <= dist[vmin.index] && !mark[vmin.index])
        {

            mark[vmin.index] = true;
            for(Liaison l : liaisons)
            {
                if((l.longueur != 0) && (l.proprietaire == 0 || l.proprietaire == joueur))
                    if(l.ville1 == vmin.index)
                        if(dist[l.ville2] > dist[vmin.index] + l.longueur || dist[l.ville2] < 0)
                        {
                            dist[l.ville2] = dist[vmin.index] + l.longueur;
                            villes[l.ville2] = vmin.index;
                            heap_push(hp, l.ville2, dist[l.ville2]); 
                        }
            }
        }
    }
    cout << endl;
}

int chemin_a_prendre(vector<Liaison>& chemin, Jeu& jeu, int joueur, int ville_depart, int ville_arrivee){
	vector<int> villes;
	
	for(int i = 0; i < jeu_nb_villes(jeu); i++)
		villes.push_back(-1);
	
	villes[ville_depart] = 0;
	

	dijkstra(jeu.liaisons, villes, joueur);
	
	if(villes[ville_arrivee] == -1) 
		return -1;	//Aucune chemin n'a été trouvé pour aller à la ville_arrivee

	int current_ville = ville_arrivee;
	Liaison shortest_liaison;
	int dist = 0;	

	
	while(current_ville != ville_depart)
	{
		for(Liaison l : jeu.liaisons)
			if(l.ville1 == villes[current_ville] && l.ville2 == current_ville && (l.proprietaire == 0 || l.proprietaire == joueur))
			{
				shortest_liaison = l;
			}
		if(shortest_liaison.proprietaire == 0)
			chemin.insert(chemin.begin(), shortest_liaison);
		current_ville = shortest_liaison.ville1;
		dist += shortest_liaison.longueur;
	}
	return dist;
}


bool cartes_necessaire_visible(Jeu& jeu, vector<Liaison> chemin, vector<int>& carte_a_prendre){
	
	int count = 0, i;
	bool found;
	for(Liaison l : chemin){
		if(count == 2)
			continue;		
		i = 0;
		found = false;
		while(i < 5 && !found){
			if(jeu.cartes_visibles[i].couleur == l.couleur){
				carte_a_prendre.push_back(i);
				count++;
				found = true;
			}
			i++;
		}
	}

	if(count > 1){
		return true;
	}else{
		return false;
	}
}



int distance_chemin_a_prendre(int nb_villes, vector<Liaison> routes, int joueur, int ville_depart, int ville_arrivee)
{
	vector<int> villes;
	
	for(int i = 0; i < nb_villes; i++)
		villes.push_back(-1);
	
	villes[ville_depart] = 0;
	

	dijkstra(routes, villes, joueur);
	
	if(villes[ville_arrivee] == -1) 
		return -1;	//Aucune chemin n'a été trouvé pour aller à la ville_arrivee

	int current_ville = ville_arrivee;
	Liaison shortest_liaison;
	int dist = 0;	

	
	while(current_ville != ville_depart)
	{
		for(Liaison l : routes)
			if(l.ville1 == villes[current_ville] && l.ville2 == current_ville && (l.proprietaire == 0 || l.proprietaire == joueur))
			{
				shortest_liaison = l;
			}
		current_ville = shortest_liaison.ville1;
		dist += shortest_liaison.longueur;
	}
	return dist;

}

/*
int dijkstra_carte(vector<Liaison>&  liaisons, vector<int>& villes, int joueur, vector<Carte> cartes, int nb_cartes)
{

    Heap hp;
    vector<int> dist = villes;
    vector<bool> mark ;
    vector<int> cartes_chemin = villes;

    for(unsigned int i = 0; i < villes.size(); i++)
    {
        mark.push_back(false);
    }
    unsigned int i = 0;
    while(i < villes.size() && villes[i] != 0)
    {
        i++;
    }
    if(i < villes.size())
    {
        heap_push(hp, i, 0);
    }


    while(heap_size(hp) > 0)
    {
        valuation vmin = heap_min(hp);
        heap_pop(hp);
        if(vmin.value <= cartes_chemin[vmin.index] && !mark[vmin.index])
        {

            mark[vmin.index] = true;
            for(Liaison l : liaisons)
            {
                if((l.longueur != 0) && (l.proprietaire == 0 || l.proprietaire == joueur))
                    if(l.ville1 == vmin.index)
		    {
			vector<int> diff = vector();
			for(int i : cartes_chemin)
			{
				
			}
                        if(dist[l.ville2] > dist[vmin.index] + l.longueur || dist[l.ville2] < 0)
                        {
                            dist[l.ville2] = dist[vmin.index] + l.longueur;
                            villes[l.ville2] = vmin.index;
                            heap_push(hp, l.ville2, dist[l.ville2]); 
                        }
		    }
            }
        }
    }
    cout << endl;	
}

int minimiser_cartes(vector<Liaison& chemin, Jeu& jeu, int joueur, int ville_depart, int ville_arrivee, vector<Carte> cartes)
{


}*/
