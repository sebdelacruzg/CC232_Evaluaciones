#include "skew_heap.h"
#include <algorithm>

using namespace std;

vector<int> encontrar_candidatos_insercion(const vector<NodoSkewHeap>& arbol, int raiz) {
    if (raiz == 0) return {};
    int nodo_columna_izquierda = 0;
    int actual = raiz;
    while (actual != 0) {
        if (arbol[actual].derecho == 0) {
            nodo_columna_izquierda = actual;
            break;
        }
        actual = arbol[actual].izquierdo;
    }
    if (nodo_columna_izquierda == 0) return {};
    vector<int> candidatos_validos;
    candidatos_validos.push_back(nodo_columna_izquierda);
    int candidato_hoja_izquierda = arbol[nodo_columna_izquierda].izquierdo;
    if (candidato_hoja_izquierda != 0) {
        if (arbol[candidato_hoja_izquierda].izquierdo == 0 && arbol[candidato_hoja_izquierda].derecho == 0) {
            candidatos_validos.push_back(candidato_hoja_izquierda);
        }
    }
    return candidatos_validos;
}

int revertir_insercion_skew_heap(vector<NodoSkewHeap>& arbol, int nodo_extraido, int raiz_actual) {
    return 0;
}

vector<int> reconstruir_permutacion(const vector<NodoSkewHeap>& arbol_inicial, int numero_nodos, bool maximizar) {
    return {};
}