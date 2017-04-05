#include "parcours.hpp"
#include "heap.cpp"
#include <cstdio>

void dijkstra(vector<Liaison>  liaisons, vector<int>& villes, int joueur)
{
    Heap hp;
    std::vector<int> dist = villes;
    std::vector<bool> mark;
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
        std::cout << vmin.index;
            mark[vmin.index] = true;
            for(Liaison l : liaisons)
            {
                if((l.longueur != 0) || (l.proprietaire == joueur || l.proprietaire == 0))
                {
                    if(l.ville1 == vmin.index)
                    {
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
    }
}

