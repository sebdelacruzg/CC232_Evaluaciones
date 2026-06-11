#include <iostream>
#include <vector>
#include <cassert>
#include "skew_heap.h"

using namespace std;

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