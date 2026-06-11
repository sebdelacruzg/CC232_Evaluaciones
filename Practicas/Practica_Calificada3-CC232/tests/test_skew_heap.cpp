#include <iostream>
#include <vector>
#include <cassert>
#include "skew_heap.h"

using namespace std;

void test_sample_1() {
    int n = 7;
    vector<NodoSkewHeap> arbol(n + 1);
    // Sample Input 1
    arbol[1].izquierdo = 2; arbol[1].derecho = 3; arbol[2].padre = 1; arbol[3].padre = 1;
    arbol[2].izquierdo = 4; arbol[2].derecho = 5; arbol[4].padre = 2; arbol[5].padre = 2;
    arbol[3].izquierdo = 6; arbol[3].derecho = 7; arbol[6].padre = 3; arbol[7].padre = 3;
    
    vector<int> min_p = reconstruir_permutacion(arbol, n, true);
    vector<int> max_p = reconstruir_permutacion(arbol, n, false);
    
    vector<int> exp_min = {1, 3, 2, 7, 5, 6, 4};
    vector<int> exp_max = {7, 1, 5, 3, 2, 6, 4};
    
    assert(min_p == exp_min);
    assert(max_p == exp_max);
    cout << "Sample 1 verificado.\n";
}

void test_invariante_columna_izquierda() {
    vector<NodoSkewHeap> arbol(5); 
    arbol[1].izquierdo = 2; arbol[2].padre = 1;
    arbol[2].izquierdo = 3; arbol[3].padre = 2;

    vector<int> candidatos = encontrar_candidatos_insercion(arbol, 1);    
    assert(!candidatos.empty());
    assert(candidatos[0] == 3);
    
    cout << "Invariante de left spine verificado!\n";
}

int main() {
    test_invariante_columna_izquierda();
    return 0;
}