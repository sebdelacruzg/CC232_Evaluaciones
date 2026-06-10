#include <iostream>
#include <vector>
#include "skew_heap.h"

using namespace std;

void resolver() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numero_nodos;
    if (!(cin >> numero_nodos)) return;
    vector<NodoSkewHeap> arbol_estado_final(numero_nodos + 1);
    for (int i = 1; i <= numero_nodos; ++i) {
        int l, r;
        cin >> l >> r;
        arbol_estado_final[i].izquierdo = l;
        arbol_estado_final[i].derecho = r;
        if (l != 0) arbol_estado_final[l].padre = i;
        if (r != 0) arbol_estado_final[r].padre = i;
    }
    vector<int> permutacion_minima = reconstruir_permutacion(arbol_estado_final, numero_nodos, true);
    if (permutacion_minima.empty()) {
        cout << "impossible\n";
        return;
    }
    vector<int> permutacion_maxima = reconstruir_permutacion(arbol_estado_final, numero_nodos, false);
    for (int i = 0; i < numero_nodos; ++i) {
        cout << permutacion_minima[i] << (i == numero_nodos - 1 ? "" : " ");
    }
    cout << "\n";

    for (int i = 0; i < numero_nodos; ++i) {
        cout << permutacion_maxima[i] << (i == numero_nodos - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    resolver();
    return 0;
}