#include "parcours.hpp"
#include "heap.cpp"

void dijkstra(Vector<Liaison>  liaisons, vector<int> villes, int joueur)
{
    heap hp;
    std::vector<int> dist = villes;
    int i = 0;
    while(i < villes.size() && villes[i] != 0)
    {
        i++;
    }
    if(i < villes.size())
    {
        valuation* v = new valuation;
        v->index = i;
        v->value = dist[i];
        heap_push(hp, v);
    }

    while(heap_size(h) > 0)
    {
        valuation vmin = heap_min(h);
        heap_pop(h);
        if(vmin.value <= dist[vmin.index])
        {
            for(Liaison l : liaisons)
            {
                if((l.longueur != 0) || (l.proprietaire == joueur || l.proprietaire == 0))
                {
                    if(ville1 == vmin.index)
                    {
                        dist[ville2]
                    }
                }
            }
        }
    }
}

