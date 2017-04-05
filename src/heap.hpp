#ifndef HUFF_HEAP_HPP
#define HUFF_HEAP_HPP


/* Type pour la file a priorite */
struct valuation{
    int index;
    int value;
};
typedef std::vector<valuation> Heap ;

/* Taille de la file a priorite */

int heap_size(Heap& h) ;

/* Sommet de la file a priorite =>valuation avec le poids minimal */

valuation heap_min(Heap& h) ;

/* Retrait de la valuation de poids minimal de la file */

void heap_pop(Heap& h) ;

/* Ajout d'une valuation a la file */

void heap_push(Heap& h, int index, int value) ;

#endif
