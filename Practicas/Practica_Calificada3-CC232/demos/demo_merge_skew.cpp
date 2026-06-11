#include <iostream>
#include <vector>
#include "skew_heap.h"

using namespace std;

int merge_demo(vector<NodoSkewHeap>& arbol, int h1, int h2) {
    if (h1 == 0) return h2;
    if (h2 == 0) return h1;
    // Mantener propiedad de min-heap
    if (h1 > h2) swap(h1, h2);
    cout << "Merge nodo " << h1 << " con nodo " << h2 << "\n";
    int sub_merge = merge_demo(arbol, arbol[h1].derecho, h2);
    arbol[h1].derecho = sub_merge;
    arbol[sub_merge].padre = h1;
    cout << "Swap en nodo " << h1 << " | Antes -> izq: " << arbol[h1].izquierdo << ", der: " << arbol[h1].derecho;
    swap(arbol[h1].izquierdo, arbol[h1].derecho);
    cout << " | Despues -> izq: " << arbol[h1].izquierdo << ", der: " << arbol[h1].derecho << "\n";

    return h1;
}

int main() {
    vector<NodoSkewHeap> arbol(5);
    int raiz_h1 = 1;
    int raiz_h2 = 2;
    cout << "--- Iniciar Demo Merge ---\n";
    int nueva_raiz = merge_demo(arbol, raiz_h1, raiz_h2);
    cout << "--- Resultado Final ---\n";
    cout << "Raiz: " << nueva_raiz << "\n";
    cout << "Hijo izq: " << arbol[nueva_raiz].izquierdo << "\n";
    cout << "Hijo der: " << arbol[nueva_raiz].derecho << "\n";

    return 0;
}