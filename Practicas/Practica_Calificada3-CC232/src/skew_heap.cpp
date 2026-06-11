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
    int hijo_izquierdo_promovido = arbol[nodo_extraido].izquierdo;
    int padre_nodo_extraido = arbol[nodo_extraido].padre;
    int nueva_raiz = raiz_actual;
    if (padre_nodo_extraido == 0) {
        nueva_raiz = hijo_izquierdo_promovido;
        if (hijo_izquierdo_promovido != 0) arbol[hijo_izquierdo_promovido].padre = 0;
    } else {
        arbol[padre_nodo_extraido].izquierdo = hijo_izquierdo_promovido;
        if (hijo_izquierdo_promovido != 0) arbol[hijo_izquierdo_promovido].padre = padre_nodo_extraido;
    }
    arbol[nodo_extraido].izquierdo = arbol[nodo_extraido].derecho = arbol[nodo_extraido].padre = 0;
    int actual = padre_nodo_extraido;
    while (actual != 0) {
        swap(arbol[actual].izquierdo, arbol[actual].derecho);
        actual = arbol[actual].padre;
    }
    return nueva_raiz;
}

vector<int> reconstruir_permutacion(const vector<NodoSkewHeap>& arbol_inicial, int numero_nodos, bool maximizar) {
    vector<NodoSkewHeap> arbol_trabajo = arbol_inicial;
    int raiz_actual = (numero_nodos > 0) ? 1 : 0; 
    vector<int> permutacion_revertida;
    for (int i = 0; i < numero_nodos; ++i) {
        vector<int> candidatos = encontrar_candidatos_insercion(arbol_trabajo, raiz_actual);
        if (candidatos.empty()) return {};
        int nodo_elegido;
        if (maximizar) {
            nodo_elegido = candidatos[0];
            for (int c : candidatos) {
                if (c > nodo_elegido) nodo_elegido = c;
            }
        } else {
            nodo_elegido = candidatos[0];
            for (int c : candidatos) {
                if (c < nodo_elegido) nodo_elegido = c;
            }
        }
        permutacion_revertida.push_back(nodo_elegido);
        raiz_actual = revertir_insercion_skew_heap(arbol_trabajo, nodo_elegido, raiz_actual);
    }
    reverse(permutacion_revertida.begin(), permutacion_revertida.end());
    return permutacion_revertida;
}