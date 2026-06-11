#ifndef SKEW_HEAP_H
#define SKEW_HEAP_H
#include <vector>

struct NodoSkewHeap {
    int izquierdo = 0;
    int derecho = 0;
    int padre = 0;
};

std::vector<int> encontrar_candidatos_insercion(const std::vector<NodoSkewHeap>& arbol, int raiz);
int revertir_insercion_skew_heap(std::vector<NodoSkewHeap>& arbol, int nodo_extraido, int raiz_actual);
std::vector<int> reconstruir_permutacion(const std::vector<NodoSkewHeap>& arbol_inicial, int numero_nodos, bool maximizar);

#endif