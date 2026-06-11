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

void test_sample_2() {
    int n = 2;
    vector<NodoSkewHeap> arbol(n + 1);
    // Sample Input 2
    arbol[1].izquierdo = 0; arbol[1].derecho = 2; arbol[2].padre = 1;
    
    vector<int> min_p = reconstruir_permutacion(arbol, n, true);
    assert(min_p.empty());
    cout << "Sample 2 verificado.\n";
}

void test_sample_3() {
    int n = 3;
    vector<NodoSkewHeap> arbol(n + 1);
    // Sample Input 3
    arbol[1].izquierdo = 2; arbol[1].derecho = 0; arbol[2].padre = 1;
    arbol[2].izquierdo = 3; arbol[2].derecho = 0; arbol[3].padre = 2;
    
    vector<int> min_p = reconstruir_permutacion(arbol, n, true);
    vector<int> max_p = reconstruir_permutacion(arbol, n, false);
    
    vector<int> exp_min = {2, 3, 1};
    vector<int> exp_max = {3, 2, 1};
    
    assert(min_p == exp_min);
    assert(max_p == exp_max);
    cout << "Sample 3 verificado.\n";
}

int main() {
    cout << "Iniciando pruebas completas...\n";
    test_sample_1();
    test_sample_2();
    test_sample_3();
    cout << "Todos los casos validados exitosamente.\n";
    return 0;
}