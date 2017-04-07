#include "parcours.hpp"
#include "heap.cpp"
#include <cstdio>

using namespace std;


void dijkstra(vector<Liaison>  liaisons, vector<int>& villes, int joueur)
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
        	cout << "Plus court chemin :" << vmin.index << endl;
            mark[vmin.index] = true;
            for(Liaison l : liaisons)
            {
                if((l.longueur != 0) || (l.proprietaire == joueur || l.proprietaire == 0))
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
}

void chemin_a_prendre(vector<Liaison> chemin, Jeu& jeu, int joueur){
	vector<int> villes;
	
	for(int i = 0; i < jeu_nb_villes(jeu); i++)
		villes.push_back(-1);
	
	villes[0] = 0;
	
	//dijkstra(jeu.liaisons, villes, 1);

	//for(unsigned int i = 0; i < villes.size(); i++)
	//	std::cout << i << "   " <<villes[i] << "\n";

	dijkstra(jeu.liaisons, villes, joueur);

	for(unsigned int i = 0; i < villes.size()-1; i++){
		for(Liaison l : jeu.liaisons){
			if(l.ville1 == villes[i] && l.ville2 == villes[i+1]){
				chemin.push_back(l);
				//cout << "liaisons " << i << " : " << l.ville1 << " " << l.ville2 <<endl;
			}
		}
		//cout << villes[i] << endl; //position de i dans la table
	}
}


bool cartes_necessaire_visible(Jeu& jeu, vector<Liaison> chemin, vector<int> carte_a_prendre){
	
	int count = 0, i = 0;
	for(Liaison l : chemin){
		for(Carte c : jeu.cartes_visibles){
			if(c.couleur == l.couleur){
				carte_a_prendre.push_back(i);
				count++;
			}
		}
		i++;
	}

	if(count > 1){
		return true;
	}else{
		return false;
	}
}