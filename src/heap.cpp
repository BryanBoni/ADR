#include "heap.hpp"


int heap_size(Heap& h) {
  return h.size() ;
}

valuation heap_min(Heap& h) {
  return h[0] ;
}

static bool comp(valuation* a1, valuation* a2) {
  return a1->value > a2->value ;
}

void heap_pop(Heap& h) {
  std::pop_heap(h.begin(), h.end(), huff_comp) ;
//  valuation v = h.back;
  h.pop_back() ;
//  free(v);
}

void heap_push(Heap& h, valuation* a) {
  h.push_back(a) ;
  std::push_heap(h.begin(), h.end(), comp) ;
}
